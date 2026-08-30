# Firmware

ESP32 controller for the re:plate dryer.

**Lead:** Ariunsaikhan Batsaikhan
**Status:** Written against the Phase 0 design. **Not yet run on hardware.**

---

## Environment

- Arduino IDE with **ESP32 board package 3.x** (`analogWrite` requires 3.x)
- Board: ESP32 DevKit v1

**Libraries**

| Library | Author |
|---|---|
| OneWire | Paul Stoffregen |
| DallasTemperature | Miles Burton |
| HX711 | bogde |
| DHT sensor library | Adafruit |
| SD | built in |

---

## Control strategy

A six-state machine: `IDLE → PREHEAT → DRY → MILL → COOL → DONE`, plus `FAULT`.

**Temperature control is hysteresis, not PID.** This is a deliberate choice.
The vessel has large thermal mass and slow response, the setpoint is fixed, and
a ±3 °C band is well inside what the process tolerates. PID would add tuning
work and failure modes for no measurable benefit. If Phase 1 data shows
unacceptable overshoot, this decision will be revisited and recorded.

**Agitation is intermittent** — 20 s on, 8 min off. Continuous mixing wastes
motor life and pumps heat out of the mass without improving drying.

**The cycle ends on mass, not time.** Target is 35% of initial mass. This is the
correct termination condition because the load cell measures the thing we
actually care about.

---

## Safety layers in firmware

These are a *second* layer. The thermal fuse and lid interlock are hardware and
function with the ESP32 removed. See [`../docs/safety.md`](../docs/safety.md).

- `setHeater()` refuses to energise on an implausible or over-temperature reading
- Global over-temperature abort, checked every loop regardless of state
- Global cycle-time ceiling of 8 hours
- Lid state checked in `setMotor()` on every call
- Sensor disconnect (out-of-range reading) triggers `FAULT`

---

## Load cell calibration

`scale.set_scale(420.0)` is a placeholder. The real value must be measured:

1. Flash with `set_scale(1.0)`
2. With nothing on the cells, call `tare()`
3. Place a **known mass** (e.g. 500 g of water)
4. Divide the raw reading by 500
5. That quotient is the scale factor — write it back

Verify against a kitchen scale across at least three different masses before
trusting any logged data.

---

## Log format

Written to `/replate.csv` on the SD card at 0.2 Hz:

```
sec,state,t_core,t_exh,rh,mass_g,heater,mixing
```

This file is the primary experimental output. Raw logs from every run —
including failed ones — are committed to [`../data`](../data).

---

## Build order for testing

Do not flash the whole sketch onto a fully wired machine. Bring it up in stages,
verifying each before adding the next:

1. DS18B20 only — print to serial, warm a sensor by hand, confirm response
2. Add HX711 — calibrate, verify in grams against a kitchen scale
3. Add SSR — **drive an LED, not a heater** — confirm switching logic
4. Add SD logging — open the CSV on a computer, plot it
5. Only then connect the heater, with someone at the disconnect switch

---

## Known limitations

- `analogWrite` on ESP32 requires core 3.x; will not compile on 2.x
- No PID; hysteresis only (see above)
- No display; serial and SD only
- Motor current sensing is specified in the design but not yet implemented —
  it is required for the Phase 3 torque measurement
- Single DHT22 in code; the design calls for inlet and exhaust sensors
