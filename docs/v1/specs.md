# Prototype v1, as-built specification

Measured, not estimated. Leave a field blank rather than guessing, a blank is
a task, a guess is an error that gets quoted later.

**Measured by:**
**Date:**

---

## Vessel

| | Value |
|---|---|
| Internal diameter | |
| Internal height | |
| Material | |
| Wall thickness | |
| Working volume | |
| Typical batch mass processed | |
| Insulation | |

## Heating

| | Value |
|---|---|
| Element type | |
| Rated power (from label) | |
| Supply voltage | |
| How switched | |
| Temperature control | |
| Temperature sensing | |
| Thermal protection fitted | |

## Agitation

| | Value |
|---|---|
| Motor type | |
| Rated voltage / current | |
| Rated speed | |
| Gearing | |
| Blade count and dimensions | |
| Blade material and thickness | |
| Blade tip clearance to wall | |
| Shaft diameter | |
| Bearings | |
| Shaft seal | |

## Airflow

| | Value |
|---|---|
| Fan type and size | |
| Rated airflow | |
| Inlet arrangement | |
| Exhaust arrangement | |
| Filtration | |

## Overall

| | Value |
|---|---|
| External W × D × H | |
| Total mass | |
| Typical cycle time as run | |
| Power supply arrangement | |

---

## Observed behaviour

Describe what actually happens, in plain terms. Approximate is fine here as
long as it is labelled approximate, this section is observation, not
measurement.

**Overheating**, at what point in the cycle, how hot does it feel or read,
what happens next:

**Anomalies under load**, what exactly is inconsistent, and under what
conditions:

**Efficiency**, how long a cycle takes, how much material goes in, how much
comes out:

---

## Comparison against the v2 design point

Fill once the fields above are complete. This table is the argument for why v2
is a smaller machine, and it needs real numbers on the left.

| Parameter | v1 as built | v2 target |
|---|---|---|
| Batch capacity | | 1.0 kg |
| Cycle time | | 4-5 h |
| Heater rating | | 400 W duty-cycled |
| Temperature control | | Closed loop, hysteresis ±3 °C |
| Instrumentation | none | Load cell, 2 × temperature, 2 × humidity, motor current |
| Specific energy | unknown | 1.21 kWh/kg water |
