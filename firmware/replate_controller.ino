/* ==============================================================
   re:plate v1.0 — food waste dryer controller
   Board: ESP32 DevKit v1 (Arduino-ESP32 core 3.x)

   Libraries: OneWire, DallasTemperature, HX711 (bogde),
              DHT sensor library (Adafruit), SD

   STATUS: written against the Phase 0 design, not yet run on
   hardware. Untested code. Do not connect a heater until the
   sensor and SSR paths have been verified separately.
   ============================================================== */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

/* ---------- PIN MAP ---------- */
const int PIN_TEMP    = 4;    // DS18B20 bus (4.7k pull-up required)
const int PIN_SSR     = 5;    // Solid-state relay — heater
const int PIN_HX_DT   = 16;   // HX711 data
const int PIN_HX_SCK  = 17;   // HX711 clock
const int PIN_DHT     = 18;   // DHT22 — exhaust
const int PIN_M_RPWM  = 25;   // BTS7960 forward
const int PIN_M_LPWM  = 26;   // BTS7960 reverse (jam clearing)
const int PIN_M_EN    = 27;   // BTS7960 enable
const int PIN_FAN     = 32;   // Blower PWM
const int PIN_LID     = 33;   // Lid switch (LOW = closed)
const int PIN_SD_CS   = 15;   // SD card chip select
const int PIN_BTN     = 34;   // Start button (input only pin)

/* ---------- SETPOINTS ---------- */
const float T_TARGET      = 65.0;   // Target core temperature, °C
const float T_HYST        =  3.0;   // Hysteresis band — limits SSR cycling
const float T_ABORT       = 95.0;   // Hard abort threshold
const float T_COOL_END    = 40.0;   // Cool-down complete
const float MASS_END_FRAC = 0.35;   // Stop at 35% of initial mass

const unsigned long MIX_ON    = 20000UL;    // Agitate 20 s
const unsigned long MIX_OFF   = 480000UL;   // Rest 8 min
const unsigned long LOG_EVERY = 5000UL;     // Log every 5 s
const unsigned long RUN_MAX   = 28800000UL; // 8 h ceiling

const int FAN_DRY   = 180;   // 0–255. THIS IS THE PHASE 2 VARIABLE.
const int FAN_COOL  = 255;
const int MOTOR_PWM = 200;

/* ---------- OBJECTS ---------- */
OneWire oneWire(PIN_TEMP);
DallasTemperature tempSensors(&oneWire);
HX711 scale;
DHT  dht(PIN_DHT, DHT22);
File logFile;

/* ---------- STATE ---------- */
enum State { IDLE, PREHEAT, DRY, MILL, COOL, DONE, FAULT };
State state = IDLE;
const char* stateName[] = {"IDLE","PREHEAT","DRY","MILL","COOL","DONE","FAULT"};

float tCore = 0, tExh = 0, rh = 0, mass = 0, mass0 = 0;
unsigned long tRunStart = 0, tLastLog = 0, tMixChange = 0;
bool mixing = false, heaterOn = false;
String faultMsg = "";

/* ================= HELPERS ================= */

void fault(String msg) {
  faultMsg = msg;
  state = FAULT;
  digitalWrite(PIN_SSR, LOW);        // heater off, unconditionally
  digitalWrite(PIN_M_EN, LOW);
  analogWrite(PIN_FAN, FAN_COOL);    // keep cooling
  Serial.print("FAULT: "); Serial.println(msg);
}

void setHeater(bool on) {
  // Refuse to energise on an implausible or dangerous reading.
  // This is a second layer only — the thermal fuse is the safety system.
  if (tCore < -50 || tCore > T_ABORT) on = false;
  heaterOn = on;
  digitalWrite(PIN_SSR, on ? HIGH : LOW);
}

void setMotor(bool on, bool reverse = false) {
  if (digitalRead(PIN_LID) == HIGH) on = false;   // lid open → motor stops
  digitalWrite(PIN_M_EN, on ? HIGH : LOW);
  analogWrite(PIN_M_RPWM, (on && !reverse) ? MOTOR_PWM : 0);
  analogWrite(PIN_M_LPWM, (on &&  reverse) ? MOTOR_PWM : 0);
}

void readSensors() {
  tempSensors.requestTemperatures();
  float a = tempSensors.getTempCByIndex(0);
  float b = tempSensors.getTempCByIndex(1);
  if (a > -50 && a < 200) tCore = a;
  else if (state != IDLE) fault("Core temperature sensor unreadable");
  if (b > -50 && b < 200) tExh = b;

  float h = dht.readHumidity();
  if (!isnan(h)) rh = h;

  if (scale.is_ready()) mass = scale.get_units(3);
}

void logRow() {
  unsigned long t = (millis() - tRunStart) / 1000;
  String row = String(t) + "," + stateName[state] + ","
             + String(tCore,2) + "," + String(tExh,2) + ","
             + String(rh,1)    + "," + String(mass,1) + ","
             + String(heaterOn) + "," + String(mixing);
  Serial.println(row);
  logFile = SD.open("/replate.csv", FILE_APPEND);
  if (logFile) { logFile.println(row); logFile.close(); }
}

/* Intermittent agitation. Continuous mixing is unnecessary and
   wastes both motor life and heat. */
void handleMixing() {
  unsigned long now = millis();
  if ( mixing && now - tMixChange > MIX_ON)  { mixing = false; tMixChange = now; }
  if (!mixing && now - tMixChange > MIX_OFF) { mixing = true;  tMixChange = now; }
  setMotor(mixing);
}

/* ================= SETUP ================= */

void setup() {
  Serial.begin(115200);

  pinMode(PIN_SSR, OUTPUT);    digitalWrite(PIN_SSR, LOW);
  pinMode(PIN_M_EN, OUTPUT);   digitalWrite(PIN_M_EN, LOW);
  pinMode(PIN_M_RPWM, OUTPUT); pinMode(PIN_M_LPWM, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_LID, INPUT_PULLUP);
  pinMode(PIN_BTN, INPUT);

  tempSensors.begin();
  dht.begin();
  scale.begin(PIN_HX_DT, PIN_HX_SCK);
  scale.set_scale(420.0);   // CALIBRATE THIS — see firmware/README.md
  scale.tare();

  if (!SD.begin(PIN_SD_CS)) {
    Serial.println("Warning: SD card not found — logging disabled");
  } else {
    logFile = SD.open("/replate.csv", FILE_APPEND);
    if (logFile) {
      logFile.println("sec,state,t_core,t_exh,rh,mass_g,heater,mixing");
      logFile.close();
    }
  }
  Serial.println("re:plate ready. Press start.");
}

/* ================= MAIN LOOP ================= */

void loop() {
  readSensors();

  // Global safety checks, independent of state
  if (tCore > T_ABORT && state != FAULT) fault("Over-temperature");
  if (state != IDLE && state != DONE && state != FAULT
      && millis() - tRunStart > RUN_MAX) fault("Cycle time exceeded");

  switch (state) {

    case IDLE:
      setHeater(false); setMotor(false); analogWrite(PIN_FAN, 0);
      if (digitalRead(PIN_BTN) == HIGH && digitalRead(PIN_LID) == LOW) {
        delay(50);
        if (digitalRead(PIN_BTN) != HIGH) break;   // debounce
        mass0 = mass;
        if (mass0 < 200) { Serial.println("Load too small"); break; }
        tRunStart = tMixChange = millis();
        state = PREHEAT;
        Serial.print("Started. Initial mass: "); Serial.println(mass0);
      }
      break;

    case PREHEAT:
      setHeater(tCore < T_TARGET);
      analogWrite(PIN_FAN, 60);        // low flow — conserve heat
      handleMixing();
      if (tCore >= T_TARGET - T_HYST) state = DRY;
      break;

    case DRY:
      // Hysteresis control. Simpler than PID and adequate here, given
      // the large thermal mass and slow response of the vessel.
      if (tCore < T_TARGET - T_HYST) setHeater(true);
      if (tCore > T_TARGET + T_HYST) setHeater(false);
      analogWrite(PIN_FAN, FAN_DRY);
      handleMixing();
      if (mass <= mass0 * MASS_END_FRAC) {
        state = MILL; tMixChange = millis();
        Serial.println("Drying complete → milling");
      }
      break;

    case MILL:
      setHeater(false);
      analogWrite(PIN_FAN, FAN_DRY);
      setMotor(true);                              // continuous
      if (millis() - tMixChange > 180000UL) state = COOL;   // 3 min
      break;

    case COOL:
      setHeater(false);
      analogWrite(PIN_FAN, FAN_COOL);
      handleMixing();
      if (tCore < T_COOL_END) {
        state = DONE;
        Serial.print("COMPLETE. Mass: "); Serial.print(mass0);
        Serial.print(" → "); Serial.print(mass);
        Serial.print(" g ("); Serial.print(100.0*(1-mass/mass0),1);
        Serial.println("% reduction)");
      }
      break;

    case DONE:
    case FAULT:
      setHeater(false); setMotor(false);
      analogWrite(PIN_FAN, (tCore > T_COOL_END) ? FAN_COOL : 0);
      break;
  }

  if (millis() - tLastLog > LOG_EVERY && state != IDLE) {
    tLastLog = millis();
    logRow();
  }
  delay(200);
}
