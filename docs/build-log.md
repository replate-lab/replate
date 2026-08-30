# Build log

One dated entry per working session, including sessions where nothing worked.
Reconstructing this later is impossible; keeping it costs ten minutes a session.

Newest entries at the bottom.

> **Note to the team:** entries below marked `[date?]` need the real date filled
> in. Put in when the decision actually happened, not today's date. If you are
> unsure of the exact day, write the week — an approximate real date is honest,
> a precise invented one is not.

---

## [date?] — Project reframed from composting to a machine

Original concept was a food waste → бордоо composting project. Reframed as a
mechanical engineering build: the interesting problem is not that decomposition
happens, it is designing a machine that accelerates and controls it.

Reasoning: composting as a topic is well covered and biological. Thermal
management, mass transfer, machine design, and closed-loop control are the parts
we can actually engineer and measure.

---

## [date?] — Process selection: dryer over inoculated digester

Two viable architectures were considered.

**A — fast-cycle dryer + grinder** (Lomi / FoodCycler approach). Grind, heat,
dry to a stable soil amendment in 4–6 hours.

**B — inoculated warm digester** (Reencle approach). Hold ~50 °C with a
microbial inoculum for 24 h+, output closer to finished compost.

**Chose A.** The deciding argument was not cost — the two are within roughly
$100 of each other. It was determinism and iteration rate:

| | A: dryer | B: digester |
|---|---|---|
| Cycle time | 6 h | 24 h+ |
| Culture establishment | none | 1–2 weeks |
| Runs possible in 10 weeks | 30–50 | 6–10 |
| Failed run interpretable? | yes | often not |

The dryer is governed by physics we can calculate and verify. The digester adds
biological failure modes we cannot diagnose — a dead culture gives one signal
and a dozen candidate causes. Critically, the *mechanical* engineering content
is nearly identical in both, so B would cost significant risk for almost no
additional value in the discipline we are working in.

Anaerobic digestion was ruled out earlier for methane handling and cycle length.

---

## [date?] — Scale and budget revised

Batch size reduced from 2.0 kg to 1.0 kg; budget from $443 to $225.

Key cost decisions:
- Vessel and heater sourced as a used rice cooker rather than separate
  components — $12 instead of ~$55, and it preserves factory thermal protection
- Salvaged ATX power supply instead of a purchased PSU
- Plywood frame instead of aluminium extrusion
- 30% held as contingency, deliberately

---

## 2026-08-28 — Phase 0: repository and organisation created

Set up `replate-lab` organisation and this repository. Responsibilities assigned
across the four of us and recorded in the main README.

Committed to the repository:
- Three sizing calculations, worked at the 1.0 kg design point, with all
  assumptions stated and flagged for later measurement (`/calcs`)
- Full bill of materials with sourcing and phase-by-phase order sequence
  (`/docs/bom.md`)
- Safety hazard register (`/docs/safety.md`)
- Prior art review (`/docs/prior-art.md`)
- ESP32 controller firmware, untested (`/firmware`)
- Five predictions recorded before building, in the README

**Motor selection corrected.** Initial instinct was a JGY-370 worm gearmotor,
which is the common choice in projects like this. Running the torque numbers
showed it delivers ~1.4 N·m against a 2.7 N·m design load — it would stall on
the first sticky batch. Specified a salvaged automotive wiper motor (~12 N·m)
instead. This is exactly the kind of error the calculations exist to catch, and
it was caught before spending money.

**Next:** order Phase 1 parts (~$44, long lead time from AliExpress), source
rice cooker and wiper motor locally.

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
