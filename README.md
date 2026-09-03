# re:plate

An open-source benchtop machine that dries and grinds household food waste into
a stable, storable soil amendment feedstock in under five hours.

**What we think is true:** turning food waste into fertiliser feedstock is a
mass-transfer problem, not a biological one. The machine is limited by how fast
water vapour can leave the vessel, not by how much heat goes into it. The design
follows from that.

**Status:** Prototype v1 is built and running since July 2026, with a blade
agitator, a resistive heater and an extraction fan. It works. It also overheats,
does things under load that we cannot explain, and is too big for the batch it
handles, which makes it inefficient. We are designing v2 to fix those three
problems, and this repository is where that work goes.

> **About the dates.** We started in June 2026 but only opened this repository on
> 28 August, about two and a half months in. Entries before that date were
> written from memory and are marked in the build log. Everything from 28 August
> is timestamped in the commit history. We should have started logging earlier.
> That is why the logging rules in `/data` exist now.

---

## Team

Four co-founders, Ulaanbaatar, Mongolia.

| | Responsibility |
|---|---|
| **Chinbuyan Tuvshintur** | Thermal design and energy modelling: energy balance, insulation, drying analysis |
| **Ariunsaikhan Batsaikhan** | Instrumentation and control: ESP32 firmware, sensors, data logging |
| **Tsenguun Battulga** | Mechanical design and fabrication: vessel, agitator, shaft assembly, CAD |
| **Zuliinbaysgalan Enebish** | Experimental design and analysis: test matrix, uncertainty, results |

We list responsibilities because none of us did this alone and it would be wrong
to imply otherwise. The commit history shows who did what.

## Where this came from

We started on **12 June 2026** by composting. We collected food waste from a
restaurant and made liquid fertiliser from it, in batches that ran 1 to 2.5
months. We tracked temperature and yield, and we spent a lot of time on the
smell, which we did manage to reduce. That work is still going. The fertiliser
is being tested on flowers and vegetables now.

The composting worked. We stopped relying on it for a different reason.

It took months of attention to make a small amount of fertiliser. It was slow,
it needed constant checking, and it was inconvenient enough that no ordinary
household would keep doing it. By the middle of July we could see the problem
was not the biology. The decomposition was fine. The problem was that all the
tedious mechanical work, breaking material down, keeping it warm, moving air
through it, was being done by hand.

We started building a machine on **15 July 2026**.

## Prototype v1

Blade agitator, resistive heater, extraction fan. It dries and it grinds.

Three problems, worst first:

| Problem | What we see | What we think is causing it |
|---|---|---|
| **Overheating** | Temperature climbs past the target and never settles | There is no closed loop. The heater is not switched against a measured temperature. |
| **Odd behaviour under load** | The machine behaves differently mid-cycle and we cannot say why | We do not know. v1 has no sensors and records nothing, so we can only describe the symptom. |
| **Too big, so inefficient** | The vessel is much larger than the batch it processes | Too much thermal mass and too much surface area losing heat. See the energy balance in [`/calcs`](./calcs). |

The third problem is what the calculations in this repository were for. They
point at a smaller vessel rather than a bigger heater, which is the opposite of
what we expected.

v1 has no sensors, so it cannot tell us why it misbehaves and cannot give us a
baseline to compare v2 against. Adding instrumentation is the first thing we do,
before changing anything mechanical.

## Why this repository exists

Commercial food recyclers like Lomi, Vitamix FoodCycler and Reencle cost $400 to
$600 and come as sealed boxes. They do not publish their thermal design, their
airflow rates, or their measured efficiency.

There is related open-source work. Arduino compost monitors, several good
dehydrator controllers, and academic papers on food waste drying. We could not
find a project that puts them together, one that documents a complete machine
along with the calculations that produced it and the data that tests them.

This is our attempt at that. We are building to a $225 budget against commercial
machines that cost $400 to $600, and we treat that limit as a design parameter
rather than an excuse.

## What this machine does and does not do

It does **not** make finished compost. Any machine that claims to do that in five
hours is overstating it.

What comes out is dried, ground, odourless organic material with most of the
water removed. It is stable enough to store for months. It becomes compost after
two to four weeks of curing, which is the biological process we spent our first
two months doing by hand.

```
food waste
  -> [ re:plate, 5 hours ]   -> dried feedstock
  -> [ cure bin, 3 weeks ]   -> compost
```

Our claim is thermal and mechanical. We know what the biological stage costs in
time and effort because we did it ourselves.

## The thermal argument

About 75% of food waste by mass is water. Removing it takes so much of the energy
budget that every other decision, heater rating, insulation thickness, vessel
size, control strategy, follows from it.

The part that surprised us is the coupling. Airflow is what physically carries
water vapour out of the vessel, so more air dries faster. But the same air also
carries heat out, so more air costs more energy per kilogram of water removed.
Drying quickly and drying efficiently work against each other.

There is an optimum somewhere. It depends on the machine's own geometry and
thermal mass, we cannot derive it on paper, and the only way to find it is to
measure. That is the main experiment in this project.

## v2 design targets

| Parameter | Target | Where it comes from |
|---|---|---|
| Batch capacity | 1.0 kg wet waste | Reduced from v1, see the efficiency problem above |
| Cycle time | 4 to 5 hours | Energy balance |
| Energy per cycle | 0.82 kWh | Q = 2 963 kJ at n = 0.60 |
| **Specific energy** | **1.21 kWh / kg water** | The number we are trying to reduce |
| Mass reduction | about 65% | 90% of water removed |
| Heater | 400 W, switched on and off | 206 W average over 4 hours |
| Airflow | 150 L/min, adjustable | 32 L/min is the theoretical minimum |
| Mixing torque | 2.7 N.m design load | shear stress about 15 kPa at 50 mm |
| Motor | at least 12 N.m | Sized for stalling, not for running |

For comparison, the theoretical floor from the latent heat of vaporisation is
0.67 kWh/kg, and industrial dryers manage 0.80 to 0.96. We are starting at a
predicted 1.21 and trying to bring it down.

We do not know v1's specific energy. That is the gap Phase 1 closes, and until
then we cannot honestly claim v2 is an improvement.

Full working is in [`/calcs`](./calcs).

## Predictions, written down before v2 is built

We are writing these now so they can be shown wrong later. Each one gets marked
confirmed or refuted against real data, and where we were wrong we explain the
difference rather than quietly dropping it.

| # | Prediction | Confidence | Result |
|---|---|---|---|
| 1 | Specific energy lands between 1.10 and 1.40 kWh/kg water | Moderate | |
| 2 | An airflow optimum exists, between 80 and 150 L/min | High | |
| 3 | Mixing torque peaks in the middle of the cycle, higher than at either the wet or the dry end | Moderate | |
| 4 | Drying is mostly falling-rate, with a short constant-rate period or none at all | High | |
| 5 | The rotating shaft seal is the first mechanical part to fail | Moderate | |
| 6 | v1's overheating is a control problem, not a heater problem. Closed-loop switching fixes it without changing the element | High | |
| 7 | Dropping to a 1.0 kg batch improves specific energy by more than 15% against v1 | Moderate | |

Prediction 3 is the one we are least sure about and most curious about. It
follows from the material going through a sticky, dough-like stage as it dries,
but we could not find anyone who has measured this for food waste.

Predictions 6 and 7 come straight from v1's problems and are what the next build
is meant to settle.

**Prediction 2 is already in dispute.** Our own drying model, in
[`docs/drying-model.html`](./docs/drying-model.html), puts the optimum below that
range. We are leaving both numbers here rather than quietly correcting one. The
measurement decides.

## Instrumentation

v1 has none. v2 is built to produce data as well as output.

- **Load cell under the vessel**, mass against time at 0.2 Hz. This gives the
  drying curve directly and is our main dataset.
- **Two temperature sensors**, core and exhaust, for thermal behaviour and heat
  loss.
- **Inlet and exhaust humidity**, to check the moisture pickup against the
  predicted 0.084 kg per kg of dry air.
- **Motor current**, to get mixing torque against moisture content.

We plan to fit the drying curves to the Midilli model, map specific energy
against airflow, and plot torque against moisture.

## The number that does not look good for us

At roughly 0.8 kWh per kilogram of waste, on a coal-heavy grid this machine
produces something like 0.6 kg of CO2 per batch. Sending the same waste to
landfill produces roughly 0.5 to 0.7 kg CO2-equivalent as methane.

Within the uncertainty of those figures, **it is about even.**

This is the least comfortable result we have and we are publishing it with the
emission factors it depends on rather than leaving it out. Two things follow.

First, it limits what we can honestly claim. This machine is not for a household
with room for a compost heap. There it is simply worse. It is for apartments,
where the real alternative is landfill, not composting. That is a narrower claim
than "sustainable technology" but it is the one our numbers support.

Second, it makes the efficiency work matter. Getting specific energy below 0.9
kWh/kg is the point where the machine stops being marginal. A counterflow heat
exchanger on the exhaust is our plan for that, tested by running identical
batches with and without it.

## How we are working

Each phase ends at something measurable. We do not start the next one until it
passes.

The order matters, and it is the thing v1 taught us. **Measure before rebuilding.**
v1 was built with no instrumentation, so we can describe its problems but not
diagnose them. We are not doing that again.

| Phase | Work | What has to pass |
|---|---|---|
| 1 | Instrument v1, sensors and logging, no mechanical change | A logged v1 baseline: drying curve and specific energy |
| 2 | v2 thermal rig, smaller vessel, closed-loop control | 45% mass loss or better, core held at 65 +/- 5 C, no overheating |
| 3 | Airflow and exhaust | Energy against airflow, with a visible optimum |
| 4 | Agitation | A full cycle unattended without jamming, plus a torque curve |
| 5 | Integration | Three unattended cycles in a row |
| 6 | Characterisation | Test matrix, at least 3 runs per condition, uncertainty stated |
| 7 | Heat recovery | Measured change in specific energy, with and without |

Session notes: [`/docs/build-log.md`](./docs/build-log.md).

## Repository structure

```
/calcs      sizing calculations, assumptions stated, units carried
/cad        Fusion 360 models, drawings, exports
/firmware   ESP32 controller
/data       raw logs from every run, including the failed ones
/docs       build log, wiring, bill of materials, safety notes
```

Two interactive pages, both openable in a browser:

- [`docs/v2-model.html`](./docs/v2-model.html), a 3D model of the v2 design built
  from the calculated dimensions
- [`docs/drying-model.html`](./docs/drying-model.html), a lumped-parameter drying
  model that sweeps airflow and locates the specific-energy optimum

Neither is CFD or FEA. The second one is a real model, but it has no spatial
resolution and every number it produces is a prediction we still have to test.

## Safety

This machine has mains voltage, sustained heat, steam and a powered blade in it.
v1 overheats, which is a fire risk, and we treat it as one.

In v2 we are not wiring a heating element by hand. We use a commercial appliance
switched by a solid-state relay, so its factory thermal cut-out and insulation
stay intact. We chose this specifically to remove the most dangerous step from
the build. On top of that there is a separate thermal fuse in series with the
heater, an RCD on the supply, and a lid interlock switch that cuts motor power in
hardware rather than in software.

Full notes in [`/docs/safety.md`](./docs/safety.md). Read them before building
anything from this.

## Prior work

- Drying kinetics of household food waste, [PubMed 26507489](https://pubmed.ncbi.nlm.nih.gov/26507489/)
- Energy consumption of agricultural dryers, [CIGR Journal](https://cigrjournal.org/index.php/Ejounral/article/download/3863/2494/0)
- Precision dehydrator control, [truglodite/Dehydrator](https://github.com/truglodite/Dehydrator)
- ESP32 rice dryer, [qppd/Rice-Dryer](https://github.com/qppd/Rice-Dryer)

## License

Firmware under Apache 2.0. Documentation under CC BY-SA 4.0. Hardware designs
under CERN-OHL-S v2.

---

Ulaanbaatar, Mongolia. Started 12 June 2026. Where we get things wrong we will
put the correction here next to the original claim.
