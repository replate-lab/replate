# Build log

One dated entry per working session, including sessions where nothing worked.
Reconstructing this later is impossible; keeping it costs ten minutes a session.

Entries before 28 August 2026 were written retrospectively on 1 September 2026
and are dated from memory — the repository did not exist yet, so there are no
timestamps to recover them from. Entries from 28 August onward are verifiable
against this repository's commit history. Where a date is approximate it is
marked as such rather than given false precision.

Newest entries at the bottom.

---

## 2026-06-12 — Project started: composting

Began collecting food waste from a restaurant and composting it to produce
liquid fertiliser.

Batches ran 1–2.5 months each. Tracked temperature and yield throughout. Odour
was the main practical problem and we worked on it specifically — successfully;
later batches smelled substantially less than the first.

Programme detail and the logging standard for batches going forward:
[`../data/composting-2026-06/`](../data/composting-2026-06)

---

## 2026-06 to 2026-08 — Composting, and what it taught us

The composting worked. The fertiliser is real and is currently being tested on
flowers and vegetables to confirm it performs against a control.

But over two months the pattern was unmistakable: **months of attention for a
small amount of output.** Slow, effortful, and inconvenient enough that no
household would sustain it. Every batch needed manual turning, monitoring, and
patience, and the reward-to-effort ratio was poor.

The conclusion we drew, roughly mid-July: the bottleneck is not the biology.
The biology works fine. The bottleneck is that the tedious mechanical part —
breaking material down, holding it warm, moving air through it — is being done
by hand.

That is a machine's job.

---

## 2026-07-15 (approx.) — Started building the machine

Began prototype v1: blade agitator, resistive heater, extraction fan.

Design was intuition-led rather than calculated. We built what seemed
reasonable and made it work.

---

## 2026-07 to 2026-08 — v1 running, three faults identified

**It works.** v1 dries and grinds food waste. That is the headline and it is
genuinely encouraging.

Three faults, in the order they matter:

**1. Overheating.** Core temperature runs above target with no stable setpoint.
The heater is not duty-cycled against a measured temperature — it is essentially
open-loop. This is a fire risk and is being treated as one.

**2. Anomalies under load.** Behaviour is inconsistent mid-cycle in ways we
cannot characterise. And we cannot diagnose it, because **v1 has no sensors and
logs nothing.** We can describe the symptom and nothing more.

**3. Oversized and inefficient.** The vessel is medium-to-large, and for the
batch size it actually processes that is too much thermal mass and too much
heat-loss area. Energy in, output out — the ratio is poor.

The second fault is the one that changed how we work. **Building without
instrumentation means faults can be observed but not explained.** v2 is
instrumented from the start, and Phase 1 is putting sensors on v1 before
changing anything mechanical, so there is a baseline to improve against.

---

## 2026-08-28 — Repository and organisation created

Set up the `replate-lab` organisation and this repository. Responsibilities
assigned across the four of us and recorded in the main README. Apache 2.0
licence applied with all four names on the copyright line.

**Motor selection corrected.** Initial instinct for v2 was a JGY-370 worm
gearmotor, the common choice in projects like this. Running the torque numbers
showed it delivers ~1.4 N·m against a 2.7 N·m design load — it would stall on
the first sticky batch. Specified a salvaged automotive wiper motor (~12 N·m)
instead.

Caught before any money was spent. First entry in this log that justifies doing
the arithmetic before the shopping.

---

## 2026-08-30 — Phase 0 documentation committed

Committed the design work behind the v2 decisions:

- `/calcs` — three sizing calculations at the 1.0 kg design point, every
  assumption stated and tagged A1–A5 against the phase that will measure it
- `/docs/bom.md` — bill of materials with sourcing and phase-by-phase ordering
- `/docs/safety.md` — hazard register, recording whether each mitigation depends
  on firmware. Four of eight do not, by design.
- `/docs/prior-art.md` — commercial, open-source and academic review
- `/firmware` — ESP32 controller, written but not yet run on hardware

**The energy balance explains fault 3.** Heat loss scales with surface area
while useful work scales with load; an oversized vessel loses the argument
before it starts. The fix the numbers point at is a *smaller vessel*, not a
bigger heater — the opposite of the intuitive response, and the reason the
v2 design point is 1.0 kg.

Also corrected two structural errors from the 28th: `calcs/README.md` held only
a 197-byte stub, and `build-log.md` had been created at `calcs/docs/` instead of
`docs/`.

---

## 2026-09-01 — Corrected the record

The README described the project as Phase 0 with nothing built. That was wrong.
v1 has been running since July and the composting work has been running since
June.

The error understated the project rather than overstating it, but it removed the
most important thing in it: **the reason a machine exists at all.** Without the
composting months, "we decided to build a dryer" is an idea. With them, it is a
conclusion drawn from two months of doing the work by hand.

Rewritten to state the real timeline, v1's three faults, and what they changed
about how we work. Added Predictions 6 and 7, both drawn directly from v1's
observed behaviour.

**Next:** order Phase 1 parts (~$44, long lead from AliExpress); source rice
cooker, wiper motor and ATX supply locally (~$29). Instrument v1 and get a
baseline before touching anything mechanical.

---

## Template for future entries

```
## YYYY-MM-DD — [what was attempted]

Who: [names present]

What we did:

What worked:

What did not:

What we changed as a result:

Next:
```
