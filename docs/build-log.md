# Build log

One entry per working session, with the date, including the sessions where
nothing worked. We cannot reconstruct this later, and keeping it costs about ten
minutes a session.

Entries before 28 August 2026 were written on 1 September from memory, because
the repository did not exist yet and there are no timestamps to check them
against. Everything from 28 August onward can be checked against the commit
history. Where we are not sure of a date we say so instead of making one up.

Newest entries at the bottom.

---

## 2026-06-12, started composting

We began collecting food waste from a restaurant and composting it into liquid
fertiliser.

Batches ran 1 to 2.5 months each. We tracked temperature and yield. The smell
was the main practical problem and we worked on it specifically. Later batches
smelled a lot less than the first ones.

Programme detail and the logging rules for future batches:
[`../data/composting-2026-06/`](../data/composting-2026-06)

---

## 2026-06 to 2026-08, what the composting taught us

It worked. The fertiliser is real and we are testing it now on flowers and
vegetables against a control.

But after two months the pattern was obvious. Months of attention for a small
amount of output. It was slow, it needed constant turning and checking, and the
effort was out of proportion to what we got back.

The conclusion, around the middle of July, was that the biology was not the
problem. Decomposition works fine on its own. The problem was that all the
tedious mechanical work, breaking material down, keeping it warm, moving air
through it, was being done by hand.

A machine should be doing that.

---

## 2026-07-15 (approximately), started building

Prototype v1: blade agitator, resistive heater, extraction fan.

We designed it by intuition rather than by calculation. We built what seemed
sensible and got it working.

---

## 2026-07 to 2026-08, v1 running, three problems

**It works.** v1 dries and grinds food waste. That was encouraging and it is
still the main thing we have.

Three problems, worst first:

**1. Overheating.** The temperature climbs past the target and never settles.
The heater is not being switched against a measured temperature, so it is
basically running open-loop. This is a fire risk and we are treating it as one.

**2. Odd behaviour under load.** The machine does different things mid-cycle and
we cannot say why. We cannot diagnose it either, because **v1 has no sensors and
records nothing.** All we can do is describe the symptom.

**3. Too big.** The vessel is much larger than the batch it actually handles.
That means too much thermal mass to heat and too much surface area losing heat.
Energy in against material out, the ratio is bad.

The second problem changed how we work. **If you build without instrumentation
you can see the faults but you cannot explain them.** v2 gets sensors from the
start, and Phase 1 is putting sensors on v1 before we change anything mechanical,
so we have a baseline to compare against.

---

## 2026-08-28, repository and organisation created

Set up the `replate-lab` organisation and this repository. Assigned
responsibilities between the four of us and wrote them in the README. Applied
Apache 2.0 with all four names on the copyright line.

**Fixed the motor choice.** Our first idea for v2 was a JGY-370 worm gearmotor,
which is what most projects like this use. Running the torque numbers showed it
gives about 1.4 N.m against a 2.7 N.m design load, so it would stall on the first
sticky batch. We specified a salvaged car wiper motor instead, around 12 N.m.

We caught this before spending any money. It is the first thing in this log that
justifies doing the arithmetic before the shopping.

---

## 2026-08-30, Phase 0 documentation

Committed the design work behind the v2 decisions:

- `/calcs`, three sizing calculations at the 1.0 kg design point, with every
  assumption written down and tagged A1 to A5 against the phase that will test it
- `/docs/bom.md`, bill of materials with sources and a phase-by-phase order
- `/docs/safety.md`, hazard register with a column recording whether each
  protection depends on firmware. Four out of eight do not, deliberately.
- `/docs/prior-art.md`, commercial, open-source and academic review
- `/firmware`, ESP32 controller, written but not yet run on hardware

**The energy balance explains problem 3.** Heat loss goes with surface area while
useful work goes with the load, so an oversized vessel loses before it starts.
What the numbers point at is a *smaller vessel*, not a bigger heater. That was
not what we expected and it is why the v2 design point is 1.0 kg.

Also fixed two mistakes from the 28th. `calcs/README.md` only had a 197-byte stub
in it, and `build-log.md` had been created at `calcs/docs/` instead of `docs/`.

---

## 2026-09-01, corrected the record

The README said the project was at Phase 0 with nothing built. That was wrong.
v1 has been running since July and the composting has been running since June.

The mistake made the project look smaller than it is, but worse than that, it
left out the reason the machine exists at all. Without the composting months,
"we decided to build a dryer" is just an idea. With them it is a conclusion we
reached after two months of doing the work by hand.

Rewrote it with the real timeline, v1's three problems, and what they changed
about how we work. Added Predictions 6 and 7, both taken directly from what v1
does.

---

## 2026-09-01, 3D model and drying model

Added two interactive pages under `/docs`.

`v2-model.html` is a 3D model of the v2 design, with the geometry taken from the
sizing calculations rather than drawn freehand. Cutaway, exploded view, blade
rotation, airflow path.

`drying-model.html` is a lumped-parameter drying model. One energy balance and
one mass-transfer relation, integrated forward in time, with sliders for heater
power, airflow, insulation, setpoint, batch, moisture, ambient and altitude. It
sweeps airflow from 10 to 400 L/min and finds where specific energy is lowest.

Two things came out of it that we did not expect.

**The model disagrees with our own Prediction 2.** It puts the airflow optimum
below the 80 to 150 L/min range we wrote down. If the model is right then the
blower specification comes down, and we refuted our own prediction before
measuring anything. We are leaving both numbers in the README.

**Above the optimum the process is heat-limited, not airflow-limited.** Extra air
carries heat out faster than it carries vapour out. The hand calculation could
not show this because it does not integrate over time.

We also put altitude in as a parameter, because it matters. Ulaanbaatar is at
about 1300 m, so ambient pressure is around 87 kPa rather than 101. That raises
saturation humidity and helps drying, and every published figure we had been
comparing ourselves against assumes sea level.

Neither page is CFD or FEA. The drying model is a real model, but it has no
spatial resolution and cannot say anything about dead zones, channelling or hot
spots.

**Next:** order Phase 1 parts, around $44 with a long lead time from AliExpress.
Buy the rice cooker, wiper motor and ATX supply locally, around $29. Put sensors
on v1 and get a baseline before touching anything mechanical.

---

## Template for future entries

```
## YYYY-MM-DD, what we tried

Who was there:

What we did:

What worked:

What did not:

What we changed because of it:

Next:
```
