# Bill of materials

Total budget: **$225 USD**, against a commercial equivalent at $400–600.

Prices are approximate for the class of part, not quotes from a specific vendor.
Sourcing is split between AliExpress (2–4 week lead time) and Ulaanbaatar local
markets.

---

## The most consequential sourcing decision

**The heating element is not hand-wired.**

A used rice cooker is bought whole and switched by a solid-state relay on its
mains cord. This is a deliberate safety decision, not a cost shortcut:

- Factory thermal cut-out, insulation, and earthing remain intact
- The single most hazardous fabrication step in the build is removed entirely
- It is also cheaper than sourcing vessel, element, and thermal protection
  separately ($12 against roughly $55)

Cost, safety, and build time all improve from one decision. It is documented
here because the reasoning matters more than the part.

---

## Parts

| # | Item | Specification | Source | Phase | USD |
|---|---|---|---|---|---|
| 1 | Vessel + heater | Used rice cooker, 1–1.5 L, 400–600 W | Second-hand market | 1 | 12 |
| 2 | Solid-state relay | Fotek SSR-25DA + heatsink | AliExpress | 1 | 7 |
| 3 | Motor | Salvaged windscreen wiper motor, 12 V, ~45 rpm, ~12 N·m | Naran Tuul auto market | 3 | 12 |
| 4 | Motor driver | BTS7960 43 A H-bridge, reversible for jam clearing | AliExpress | 3 | 6 |
| 5 | Microcontroller | ESP32-WROOM-32 DevKit v1 | AliExpress | 1 | 5 |
| 6 | SD module | SPI micro-SD + 8 GB card | AliExpress | 1 | 3 |
| 7 | Load cells | 5 kg strain gauge × 4 + HX711 amplifier | AliExpress | 1 | 5 |
| 8 | Temperature | DS18B20 waterproof × 2 (core, exhaust) | AliExpress | 1 | 4 |
| 9 | Humidity | DHT22 × 2 (inlet, exhaust) | AliExpress | 2 | 6 |
| 10 | Blower | 12 V centrifugal, 60–80 mm, PWM-capable | AliExpress | 2 | 5 |
| 11 | Power supply | Salvaged ATX PSU (12 V, 10 A+) | Old PC | 1 | 5 |
| 12 | Shaft + bearings | 10 mm stainless shaft, 2 × flange bearing, coupler | Metal market | 3 | 14 |
| 13 | Blade stock | 3 mm stainless plate, 200 × 100 mm | Metal market | 3 | 8 |
| 14 | Insulation | Ceramic fibre blanket 25 mm, 0.5 m² | Building supplies | 1 | 8 |
| 15 | Thermal fuses | 120 °C non-resettable × 3 | AliExpress | 1 | 3 |
| 16 | Electrical safety | RCD, line fuse, terminals, high-temp wire | Electrical supplier | 1 | 15 |
| 17 | Activated carbon | 200 g, odour filter | Pharmacy / AliExpress | 2 | 4 |
| 18 | Frame | 18 mm plywood or salvaged steel | Timber market | 4 | 12 |
| 19 | Sealing | High-temp silicone, fasteners, shaft dust seal | Building supplies | 3 | 10 |
| 20 | Consumables | Breadboard, jumpers, JST connectors, solder, heat-shrink | Local electronics | 1 | 14 |
| 21 | Passives and switches | 4.7 kΩ pull-up, assorted resistors, LEDs, momentary pushbutton, **microswitch for lid interlock** | Local electronics | 1 | 8 |

| | USD |
|---|---|
| Parts subtotal | **166** |
| Contingency | **59** |
| **Total** | **225** |

### On item 21

Added 2026-09-01 after a read-through caught that the firmware and the safety
analysis both depend on parts that were never listed.

The firmware header specifies a 4.7 kΩ pull-up on the DS18B20 bus — without it
the temperature sensors do not read at all, and temperature is the one
measurement every other decision hangs on. `PIN_BTN` and `PIN_LID` likewise
assume a pushbutton and a microswitch that appeared nowhere in this list.

The microswitch is the more serious omission: it is hazard **H5** in
[`safety.md`](./safety.md), the hardware lid interlock that cuts motor power
independently of firmware. A safety mitigation that is specified but never
purchased is not a mitigation.

The LEDs exist for the staged bring-up in
[`../firmware/README.md`](../firmware/README.md) — step 3 is to drive an LED
rather than a heater while the switching logic is verified. That step is only
possible if an LED was bought.

Cost absorbed from contingency rather than by cutting elsewhere.

### On the contingency line

30% is held back deliberately. This is a first build by a team without prior
hardware experience — components will be destroyed. Budgeting for that is a
planning decision, not an admission of expected failure. Every entry is
recorded in `build-log.md` when it happens.

---

## Order sequence

Parts are ordered per phase, not all at once. The Phase 3 mechanical parts
depend on decisions that Phase 1 and 2 data will inform.

**Order now — long lead time (~$44)**
SSR, ESP32, HX711 + load cells, DS18B20 × 2, DHT22 × 2, SD module, BTS7960,
thermal fuses, blower.

**Buy locally alongside (~$22)**
Consumables and item 21. Do not wait on shipping for these — the staged
firmware bring-up needs the LEDs and the 4.7 kΩ pull-up on day one, and every
day spent waiting on a $0.05 resistor is a day the sensors cannot be tested.

**Source locally this week (~$29)**
Rice cooker, wiper motor, ATX power supply.

**Defer to Phase 3 (~$44)**
Shaft, bearings, blade stock, frame, sealing. Blade geometry is not final until
the thermal behaviour is characterised.

---

## Tools

| Category | Items |
|---|---|
| Essential | Multimeter · 60 W soldering iron · drill + metal bits · wire strippers · pliers and spanners · hacksaw |
| Measurement | Vernier caliper · 5 kg kitchen scale (load cell reference) · rule and protractor |
| Safety | Eye protection · work gloves · small dry powder extinguisher · fused extension lead |
| Outsourced | 3 mm stainless blade cutting — laser or waterjet at a metal shop, $8–15 |

Blade cutting is outsourced deliberately. Hand-cutting 3 mm stainless is slow,
imprecise, and unsafe without proper equipment. A dimensioned drawing sent to a
shop costs less than half a day and produces a better part.
