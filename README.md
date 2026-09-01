# re:plate

An open-source benchtop machine that dries and grinds household food waste into
a stable, storable soil amendment feedstock in under five hours.

**The claim this project tests:** converting food waste into fertiliser feedstock
is a mass-transfer problem, not a biological one. The machine that does it is
limited by how fast water vapour can leave the vessel — not by how much heat
goes into it. Every design decision here follows from that.

**Status:** Prototype **v1 is built and running** since July 2026 — blade
agitator, resistive heater, extraction fan. It works. It also overheats, shows
anomalies under load that we cannot yet diagnose, and is oversized badly enough
to be inefficient. **v2 is being designed to fix those three faults**, and this
repository documents that work as it happens.

---

## Team

Four co-founders. Ulaanbaatar, Mongolia.

| | Responsibility |
|---|---|
| **Chinbuyan Tuvshintur** | Thermal design and energy modelling — energy balance, insulation, drying analysis |
| **Ariunsaikhan Batsaikhan** | Instrumentation and control — ESP32 firmware, sensor integration, data logging |
| **Tsenguun Battulga** | Mechanical design and fabrication — vessel, agitator, shaft assembly, CAD |
| **Zuliinbaysgalan Enebish** | Experimental design and analysis — test matrix, uncertainty, results |

Responsibilities are stated because a project of this size cannot be honestly
credited to any one of us. The commit history records who did what, and it is
open to inspection.

## Where this came from

The project began on **12 June 2026** as a composting effort. We collected food
waste from a restaurant and produced liquid fertiliser in batches running
1–2.5 months, tracking temperature and yield, and working particularly on odour
— which we reduced substantially. That work is still running: the resulting
fertiliser is currently being tested on flowers and vegetables.

**The composting worked.** That is not why we stopped relying on it.

It took months of attention to produce a small amount of output. The process
was slow, effortful, and inconvenient enough that nobody would sustain it in an
apartment. By mid-July the bottleneck was clearly not biology — it was the
absence of a machine to do the tedious part quickly and without supervision.

We started building one on **15 July 2026**.

## Prototype v1

Blade agitator, resistive heater, extraction fan. It dries and it grinds.

Three faults, in the order they matter:

| Fault | What we observe | Suspected cause |
|---|---|---|
| **Overheating** | Core temperature runs above target with no stable setpoint | No closed-loop control. The heater is not duty-cycled against a measured temperature. |
| **Anomalies under load** | Inconsistent behaviour mid-cycle, not yet characterised | Unknown — and undiagnosable, because v1 carries no instrumentation and logs nothing. |
| **Poor efficiency** | Vessel is oversized for the batch it processes | Thermal mass and heat-loss area both scale badly against a small load. See the energy balance in [`/calcs`](./calcs). |

The third fault is what the calculations in this repository were done to answer.
They point at a **smaller vessel**, not a bigger heater — which is the opposite
of the intuitive fix.

**v1 has no sensors and produces no data.** It cannot tell us why it misbehaves,
and it cannot give us a baseline to prove v2 is any better. Instrumenting it is
the first thing we do, before changing anything mechanical.

## Why this repository exists

Commercial food recyclers — Lomi, Vitamix FoodCycler, Reencle — cost $400–600
and ship as sealed boxes. Their thermal design, airflow rates, and measured
efficiency are not published.

The open-source landscape has adjacent work: Arduino compost *monitors*, several
capable precision dehydrator controllers, and a body of academic literature on
food waste drying kinetics. We could not find a project connecting them — one
documenting a complete machine together with the sizing calculations that
produced it and the performance data that tests them.

This is an attempt at that, built to a $225 budget against a commercial
equivalent costing $400–600. The constraint is documented as a design parameter,
not an apology.

## Scope, stated precisely

This machine does **not** produce finished compost, and any five-hour machine
claiming otherwise is overstating it. The output is dried, ground, odourless,
volume-reduced organic material, stable enough to store for months. It becomes
compost after 2–4 weeks of curing — the biological process we spent our first
two months doing by hand.

```
food waste
  → [ re:plate — 5 hours ]   → dried feedstock
  → [ cure bin — 3 weeks ]   → compost
```

Our engineering claim is thermal and mechanical. We know what the biological
stage costs in time and effort, because we did it.

## The thermal argument

About 75% of food waste by mass is water. Removing it dominates the energy
budget so completely that every other decision — heater rating, insulation
thickness, vessel geometry, control strategy — is downstream of it.

The non-obvious part is the coupling. Airflow physically carries water vapour
out of the vessel, so drying rate scales with it. But the same airflow carries
sensible heat out, so energy consumed per kilogram of water removed *also*
scales with it. Fast drying and efficient drying pull in opposite directions.

There is a real optimum. It depends on the machine's specific geometry and
thermal mass, it cannot be derived from first principles, and it can only be
found by measurement. Locating it is the central experiment of this project.

## v2 design targets

| Parameter | Target | Basis |
|---|---|---|
| Batch capacity | 1.0 kg wet waste | Reduced from v1 — see efficiency fault above |
| Cycle time | 4–5 hours | Energy balance |
| Energy per cycle | 0.82 kWh | Q = 2 963 kJ at η ≈ 0.60 |
| **Specific energy** | **1.21 kWh / kg water** | Primary optimisation metric |
| Mass reduction | ~65% | 90% water removal |
| Heater | 400 W, duty-cycled | 206 W mean over 4 h |
| Airflow | 150 L/min, PWM-adjustable | 32 L/min theoretical minimum |
| Mixing torque | 2.7 N·m design | τ_shear ≈ 15 kPa, r_eff = 50 mm |
| Motor | ≥12 N·m | Sized for stall, not running load |

Reference points for specific energy: the theoretical floor set by the latent
heat of vaporisation is 0.67 kWh/kg. Industrial indirect dryers achieve
0.80–0.96. This design targets 1.21, and the work is to drive it down.

**We do not know v1's specific energy.** That is the measurement gap Phase 1
closes, and until it is closed we cannot state an improvement figure.

Full derivations with stated assumptions are in [`/calcs`](./calcs).

## Predictions, recorded before v2 is built

Committed now so that they can be shown wrong later. Each will be marked
confirmed or refuted against measured data, with the discrepancy explained
rather than quietly dropped.

| # | Prediction | Confidence | Result |
|---|---|---|---|
| 1 | v2 specific energy lands between 1.10 and 1.40 kWh/kg water | Moderate | — |
| 2 | An airflow optimum exists, between 80 and 150 L/min | High | — |
| 3 | Mixing torque peaks mid-cycle, exceeding both the wet and dry extremes | Moderate | — |
| 4 | Drying is predominantly falling-rate; any constant-rate period is short or absent | High | — |
| 5 | The rotating shaft seal is the first mechanical component to fail | Moderate | — |
| 6 | v1's overheating is a control problem, not a heater-rating problem — closed-loop duty cycling fixes it without changing the element | High | — |
| 7 | Reducing batch size to 1.0 kg improves specific energy by more than 15% against v1 | Moderate | — |

Prediction 3 is the one we are least confident in and most interested in. It
follows from the material passing through a dough-like phase as moisture drops,
but we have found no direct measurement of it for food waste.

Predictions 6 and 7 come directly from v1's observed faults and are the two the
next build is designed to settle.

## Instrumentation

v1 has none. v2 is built to produce data, not only output:

- **Load cell beneath the vessel** — mass vs. time at 0.2 Hz, yielding the drying
  curve directly. This is the primary dataset.
- **Two thermocouples** (core, exhaust) — thermal behaviour and loss estimation.
- **Inlet and exhaust humidity** — measured moisture pickup against the predicted
  Δω = 0.084 kg/kg dry air.
- **Motor current** — mixing torque as a function of moisture content.

Planned analysis: drying curves fitted against the Midilli model, the
energy-vs-airflow optimisation surface, and the torque-vs-moisture relationship.

## The number that does not flatter this project

At roughly 0.8 kWh per kilogram of waste processed, on a coal-dominated grid
this machine emits on the order of 0.6 kg CO₂ per batch. Landfilling the same
waste produces roughly 0.5–0.7 kg CO₂-equivalent through anaerobic methane.

Within the uncertainty of those figures, **it is approximately a wash.**

This is the least comfortable result in the project. It will be published with
the grid emission factors it depends on, not buried. Two things follow.

First, it constrains the honest use case. This machine is not for a household
with room for a compost heap; there it is strictly worse. It is for apartment
housing, where the realistic alternative is landfill rather than composting.
That is a narrower claim than "sustainable technology," and it is the one our
data can support.

Second, it gives the efficiency work real stakes. Moving specific energy below
0.9 kWh/kg is the threshold at which the machine becomes defensible on its own
terms rather than marginal. A counterflow exhaust heat exchanger is the planned
route, evaluated as an A/B comparison on identical batches.

## Method

Each phase ends at a measurable gate. The next does not begin until the gate
passes.

The ordering is deliberate, and it is the correction v1 taught us: **measure
before rebuilding.** v1 was built without instrumentation, so its faults can be
described but not diagnosed. We are not repeating that.

| Phase | Work | Gate |
|---|---|---|
| 1 | Instrument v1 — sensors and logging, no mechanical change | A logged v1 baseline: drying curve and specific energy |
| 2 | v2 thermal rig — reduced vessel, closed-loop control | ≥45% mass loss, core held at 65 ± 5 °C, no overheat |
| 3 | Airflow and exhaust | Energy-vs-airflow curve with visible optimum |
| 4 | Agitation | Unattended cycle without jamming; torque curve |
| 5 | Integration | Three consecutive unattended cycles |
| 6 | Characterisation | Test matrix, n ≥ 3 per condition, stated uncertainty |
| 7 | Heat recovery | Measured Δ in specific energy, with and without |

Dated session notes: [`/docs/build-log.md`](./docs/build-log.md).

## Repository structure

```
/calcs      sizing calculations, assumptions stated, units carried
/cad        Fusion 360 models, drawings, exports
/firmware   ESP32 controller
/data       raw logs from every run, including failed ones
/docs       build log, wiring, bill of materials, safety notes
```

## Safety

This machine combines mains voltage, sustained heat, steam, and a powered blade.
v1 overheats, which is a fire risk and is being treated as one.

In v2 the heating element is deliberately not hand-wired. It is a commercial
appliance switched by a solid-state relay, so its factory thermal protection and
insulation remain intact — a decision made specifically to remove the most
hazardous fabrication step from a student build. Beyond that: an independent
non-resettable thermal fuse in series with the heater, a residual-current device
on the supply, and a hardware lid interlock on the motor that does not depend on
firmware.

Full notes in [`/docs/safety.md`](./docs/safety.md). Read them before building
from this.

## Prior work

- Drying kinetics of household food waste — [PubMed 26507489](https://pubmed.ncbi.nlm.nih.gov/26507489/)
- Energy consumption of agricultural dryers — [CIGR Journal](https://cigrjournal.org/index.php/Ejounral/article/download/3863/2494/0)
- Precision dehydrator control — [truglodite/Dehydrator](https://github.com/truglodite/Dehydrator)
- ESP32 rice dryer — [qppd/Rice-Dryer](https://github.com/qppd/Rice-Dryer)

## License

Firmware under Apache 2.0. Documentation under CC BY-SA 4.0. Hardware designs
under CERN-OHL-S v2.

---

*Ulaanbaatar, Mongolia. Started 12 June 2026. Where we are wrong, the correction
will be recorded here alongside the original claim.*
