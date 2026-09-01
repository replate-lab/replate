# Data

Raw logs from every run, including failed ones.

**Lead:** Zuliinbaysgalan Enebish
**Status:** Empty, and it should not be.

Two bodies of real data exist outside this repository and need to be brought in:

1. **Composting logs, June–August 2026** — temperature and yield across batches
   of 1–2.5 months, plus the odour-reduction work. Held in personal notes.
   Transcription schema and instructions:
   [`composting-2026-06/`](./composting-2026-06)
2. **Germination trial** — the liquid fertiliser is being tested on flowers and
   vegetables. Protocol, control design, and the Zucconi maturity index:
   [`../docs/germination-trial.md`](../docs/germination-trial.md)

Neither is machine data, and both are evidence.

**Nothing in this directory is estimated.** Where a measurement was not taken,
the field stays empty and the gap is named. A labelled gap can be filled later;
an invented number that gets quoted downstream cannot be pulled back.

**Prototype v1 produces no data at all** — it carries no sensors. Instrumenting
it for a baseline is Phase 1, before any mechanical change to v2.

---

## Why failed runs are committed

A dataset containing only successful runs is not evidence, it is selection. Runs
that aborted, jammed, or produced nonsense are committed with the same care as
the ones that worked, and the build log records what we think went wrong.

Nothing is deleted from this directory. Corrections are made by adding files,
not by removing them.

---

## Log format

Written by the controller to SD at 0.2 Hz:

```
sec,state,t_core,t_exh,rh,mass_g,heater,mixing
```

| Column | Unit | Meaning |
|---|---|---|
| `sec` | s | Seconds since cycle start |
| `state` | — | PREHEAT / DRY / MILL / COOL / DONE / FAULT |
| `t_core` | °C | Core temperature (DS18B20) |
| `t_exh` | °C | Exhaust temperature (DS18B20) |
| `rh` | % | Exhaust relative humidity (DHT22) |
| `mass_g` | g | Total vessel mass (HX711 load cells) |
| `heater` | 0/1 | SSR state |
| `mixing` | 0/1 | Motor state |

## File naming

```
YYYY-MM-DD_run-NN_[condition].csv
```

Example: `2026-09-15_run-03_fan180.csv`

Every file gets a matching entry in `/docs/build-log.md` recording batch
composition, initial mass, ambient conditions, and anything unusual.

---

## Planned analysis

| Output | Source | Phase |
|---|---|---|
| Drying curves, mass vs. time | `mass_g` | 1 |
| Midilli model fit, R² and RMSE | `mass_g` | 5 |
| Specific energy vs. airflow | heater duty × time / water removed | 2 |
| Thermal efficiency η, measured | energy in vs. latent heat out | 1 |
| Torque vs. moisture content | motor current × gear ratio | 3 |
| Heat recovery A/B comparison | paired runs | 6 |

The specific-energy-vs-airflow curve is the headline result. Everything else
supports it.

---

## Measurement discipline

- Minimum **n = 3** per condition before any conclusion is drawn
- Ambient temperature and humidity recorded for every run — they affect inlet ω
- Batch composition recorded; a run on citrus peel is not comparable to one on
  mixed vegetable waste
- Uncertainty stated on every reported figure

Load cell calibration is verified against a kitchen scale before each
measurement session and the check is logged.
