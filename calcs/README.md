# Sizing calculations

All three calculations that determine component selection, worked at the 1.0 kg
design point. Assumptions are stated explicitly so they can be challenged, and
units are carried through every step.

**Lead:** Chinbuyan Tuvshintur
**Status:** Complete for the 1.0 kg design point. To be re-checked against
measured data in Phase 1 and Phase 2.

---

## 1. Energy balance → heater sizing

### Given

| Symbol | Value | Note |
|---|---|---|
| m_wet | 1.00 kg | Design batch |
| moisture fraction | 0.75 | Typical household food waste |
| m_water | 0.75 kg | |
| removal fraction | 0.90 | Target |
| m_removed | 0.675 kg | Water actually evaporated |
| c_p | 3.5 kJ/kg·K | Wet organic mass, literature value |
| h_fg | 2400 kJ/kg | Evaporation near 60 °C |
| ΔT | 45 K | 20 °C ambient → 65 °C target |
| η_system | 0.60 | Assumed, see note below |

### Working

```
Q_sensible = m · c_p · ΔT
           = 1.00 × 3.5 × 45
           = 158 kJ

Q_latent   = m_removed · h_fg
           = 0.675 × 2400
           = 1 620 kJ

Q_ideal    = 158 + 1 620
           = 1 778 kJ

Q_real     = Q_ideal / η_system
           = 1 778 / 0.60
           = 2 963 kJ
           = 0.82 kWh
```

### Result

```
Mean power over a 4 h cycle = 2 963 000 / (4 × 3600) = 206 W
→ Specify a 400 W heater, duty-cycled
```

Oversizing and duty-cycling is deliberate: it gives the controller authority to
recover after each lid opening, rather than running a marginal heater at 100%.

### Specific energy

```
1.21 kWh per kg of water removed
```

Comparison points:

| | kWh/kg water |
|---|---|
| Theoretical floor (latent heat only) | 0.67 |
| Industrial indirect dryers | 0.80-0.96 |
| **This design (predicted)** | **1.21** |

The gap between 1.21 and 0.96 is the optimisation target for Phase 6.

### On η_system = 0.60

This is the weakest assumption in the calculation and it is a guess, not a
derivation. It bundles wall conduction loss, the sensible heat carried out in
the exhaust stream, and start-up transient. A small vessel has a poor
surface-to-volume ratio, so 0.60 is chosen conservatively, lower than the
0.65-0.75 typical of larger equipment.

**Phase 1 measures this directly.** If the measured value differs materially
from 0.60, this section will be revised and the original left visible.

---

## 2. Mass transfer → blower sizing

Heat input alone does not dry anything. Air must physically carry the water
vapour out of the vessel. This calculation sizes that airflow.

### Given

| Symbol | Value | Note |
|---|---|---|
| T_exhaust | 65 °C | Assumed at equilibrium |
| ω_sat @ 65 °C | 0.18 kg/kg dry air | Psychrometric |
| pickup efficiency | 0.50 | Assumed, exhaust is not saturated |
| ω_out | 0.090 kg/kg | |
| ω_in | 0.006 kg/kg | 20 °C, 40% RH ambient |
| ρ_air @ 65 °C | 1.04 kg/m³ | |
| t_cycle | 4 h = 14 400 s | |

### Working

```
Δω      = ω_out − ω_in
        = 0.090 − 0.006
        = 0.084 kg water / kg dry air

m_air   = m_removed / Δω
        = 0.675 / 0.084
        = 8.04 kg dry air

ṁ_air   = 8.04 / 14 400
        = 5.58 × 10⁻⁴ kg/s

V̇       = ṁ_air / ρ
        = 5.58 × 10⁻⁴ / 1.04
        = 5.37 × 10⁻⁴ m³/s
        = 0.54 L/s
        = 32 L/min
```

### Result

```
Theoretical minimum: 32 L/min
→ Specify 150 L/min, PWM-adjustable
```

The margin is deliberate and it is the entire point of the design. Pickup
efficiency will be worse than 0.50 in practice, and headspace sweeping needs
volume beyond the stoichiometric minimum.

### The coupling

More airflow removes water faster but carries more sensible heat out of the
vessel, raising kWh per kg of water removed. Less airflow conserves heat but
stalls drying. Drying *rate* and drying *efficiency* are in direct opposition.

An optimum exists. It depends on this machine's specific geometry and thermal
mass, and it cannot be derived here, it must be measured. **Phase 2 finds it**
by running identical batches at four airflow settings and measuring both drying
time and specific energy.

This is the central experiment of the project.

---

## 3. Mixing torque → motor selection

### Given

| Symbol | Value | Note |
|---|---|---|
| vessel ID | 160 mm | |
| blade radius | 70 mm | |
| paddles | 2 × (60 × 30 mm) | |
| A_total | 3.6 × 10⁻³ m² | |
| τ_shear | 15 kPa | Worst case: sticky mid-dry phase |
| r_eff | 50 mm | Area centroid |
| ω | 45 rpm = 4.71 rad/s | |

### Working

```
F        = τ_shear · A
         = 15 000 × 3.6 × 10⁻³
         = 54 N

T_design = F · r_eff
         = 54 × 0.050
         = 2.7 N·m

with 2× safety factor
         = 5.4 N·m

P_mech   = T · ω
         = 2.7 × 4.71
         = 12.7 W
```

### Result

```
Running load is only ~13 W
→ Select on STALL torque, not running power: ≥12 N·m
```

### Why running power is the wrong criterion

13 W suggests a small motor. That reasoning kills the machine. It does not fail
under steady load, it fails when it **jams**, and jam torque is what must be
survived.

Worked example of the trap: the widely available `JGY-370` worm gearmotor is a
common choice for projects like this. It delivers roughly **1.4 N·m** running
and 2.5 N·m stall, well under the 2.7 N·m design load, let alone the 5.4 N·m
with margin. It would stall on the first sticky batch.

A salvaged automotive windscreen wiper motor delivers on the order of **12 N·m**
at ~45 rpm, is self-locking through its worm drive, and costs $10-15 second-hand
in Ulaanbaatar. That is the specified part.

### On τ_shear = 15 kPa

Also an estimate. Published shear strength data for partially dried food waste
is scarce, and the value is taken from the upper end of ranges reported for
comparable wet organic solids.

**Phase 3 measures it directly** by logging motor current through a full cycle
and back-calculating torque. If the real peak exceeds 15 kPa, this section is
revised and the original left visible.

---

## Summary of assumptions to be tested

| # | Assumption | Value | Tested in |
|---|---|---|---|
| A1 | System thermal efficiency | η = 0.60 | Phase 1 |
| A2 | Moisture pickup efficiency | 50% of saturation | Phase 2 |
| A3 | Peak shear stress | τ = 15 kPa | Phase 3 |
| A4 | Specific heat of wet mass | 3.5 kJ/kg·K | Phase 1 |
| A5 | Food waste moisture content | 75% | Phase 1 |

Each will be replaced by a measured value. Where the measurement disagrees with
the assumption, both numbers stay in this document.
