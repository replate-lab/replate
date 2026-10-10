# v1 surface temperatures, October 2026

One measurement session on prototype v1, taken mid-cycle with the machine
running. This is the only measured dataset in the repository so far, and it is
what the energy-balance figures quoted in the main README are derived from.

## Conditions

| | |
|---|---|
| Date | October 2026 |
| Cycle | 3 |
| Time into cycle | about 32 minutes |
| Heater nameplate | 800 W |
| Ambient | 22.1 °C |
| Internal working temperature | about 78 °C |
| Instrument | infrared thermometer, external surfaces only |

Readings are in [`surface-temps.csv`](./surface-temps.csv).

## Derived heat loss

Surface loss is calculated as `Q = A · (h_conv + h_rad) · (T_s − T_amb)` for each
region, with natural-convection and radiation coefficients evaluated at the
measured surface temperature and an emissivity of 0.9.

**This calculation rests on an assumption that has not been measured.** v1's
vessel dimensions are not recorded, because
[`docs/v1/specs.md`](../../docs/v1/specs.md) is still an empty template. The
figures below assume a vessel of roughly 250 mm diameter by 300 mm tall, which
is consistent with v1 being described as oversized. At the v2 design size of
160 × 200 mm the same temperatures would give about 53 W rather than 113 W.

| Region | Loss, W |
|---|---|
| Lid | 18 |
| Wall, upper third | 27 |
| Wall, middle third | 25 |
| Wall, lower third | 19 |
| Base | 19 |
| Shaft penetration | 2 |
| Exhaust duct | 3 |
| **Total surface** | **113** |

Against an 800 W nameplate input that is **14%**.

## Where the rest of the energy is

| Path | W | Share of 800 W |
|---|---|---|
| Surface loss, measured above | 113 | 14% |
| Exhaust sensible heat, calculated at 142 L/min and an exhaust near 55 °C | 81 | 10% |
| Evaporation, from the drying rate observed in earlier runs | about 135 | 17% |
| **Accounted for** | **329** | **41%** |
| **Not accounted for** | **471** | **59%** |

Most of the input is unexplained. Better insulation does not close a gap this
size, so the problem is probably not where we first looked.

## The reading that points somewhere

Point 9, the heater's outer surface, reads **68.2 °C** while the vessel interior
is at about **78 °C**.

A band heater that is actively delivering power has to be hotter than the vessel
it is heating. Its outer face typically sits well above the contents, often
120 °C or more. A surface 10 °C below the interior means heat is flowing the
wrong way across that boundary at the moment of measurement.

Two explanations fit:

1. The reading was taken during an off interval of the hysteresis cycle, in
   which case it means nothing.
2. The heater is not delivering anything close to 800 W.

## Next measurement

A plug-in energy meter on the supply, one full cycle, read the total kWh.

| Result | Meaning |
|---|---|
| 2.5 to 3.0 kWh | The heater is working. The loss is somewhere we have not looked. |
| 0.8 to 1.0 kWh | The heater is delivering roughly a third of nameplate. |

If it is the second, the things to check are contact between the band and the
vessel wall, supply voltage, SSR switching, and element resistance, which should
read about 60 Ω for an 800 W element on 220 V.

## What this dataset is not

A single session, one cycle, one set of readings, no repeats. It is enough to
locate a problem and not enough to characterise one. It is published because the
main README quotes numbers from it and those numbers should be checkable.
