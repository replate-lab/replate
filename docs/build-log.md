# Build log

One dated entry per working session, including sessions where nothing worked.
Reconstructing this later is impossible; keeping it costs ten minutes a session.

Newest entries at the bottom.

Dates from 2026-08-28 onward are verifiable against this repository's commit
history. The reframing entry predates the repository and is dated from memory —
see the note on it.

---

## 2026-08 — Project reframed from composting to a machine

> **Exact date not recorded.** This decision predates the repository, so there
> is no timestamp to recover it from. Dated to the month rather than invented to
> the day. If someone remembers the week, narrow it.

Original concept was a food waste → бордоо composting project. Reframed as a
mechanical engineering build: the interesting problem is not that decomposition
happens, it is designing a machine that accelerates and controls it.

Reasoning: composting as a topic is well covered and biological. Thermal
management, mass transfer, machine design, and closed-loop control are the parts
we can actually engineer and measure.

---

## 2026-08-28 — Process selection: dryer over inoculated digester

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

## 2026-08-28 — Scale and budget revised

Batch size reduced from 2.0 kg to 1.0 kg; budget from $443 to $225.

Key cost decisions:
- Vessel and heater sourced as a used rice cooker rather than separate
  components — $12 instead of ~$55, and it preserves factory thermal protection
- Salvaged ATX power supply instead of a purchased PSU
- Plywood frame instead of aluminium extrusion
- 30% held as contingency, deliberately

---

## 2026-08-28 — Repository and organisation created

Set up the `replate-lab` organisation and this repository. Responsibilities
assigned across the four of us and recorded in the main README. Apache 2.0
licence applied with all four names on the copyright line.

**Motor selection corrected.** Initial instinct was a JGY-370 worm gearmotor,
the common choice in projects like this. Running the torque numbers showed it
delivers ~1.4 N·m against a 2.7 N·m design load — it would stall on the first
sticky batch. Specified a salvaged automotive wiper motor (~12 N·m) instead.

This is exactly the kind of error the calculations exist to catch, and it was
caught before any money was spent. It is the first entry in this log that
justifies doing the arithmetic before the shopping.

---

## 2026-08-30 — Phase 0 documentation committed

Committed the design work behind the decisions above:

- `/calcs` — three sizing calculations worked at the 1.0 kg design point, with
  every assumption stated and tagged A1–A5 against the phase that will measure it
- `/docs/bom.md` — bill of materials with sourcing and a phase-by-phase order
  sequence, so mechanical parts are not bought before thermal data exists
- `/docs/safety.md` — hazard register, with a column recording whether each
  mitigation depends on firmware. Four of eight do not, by design.
- `/docs/prior-art.md` — commercial, open-source and academic review
- `/firmware` — ESP32 controller, written but not yet run on hardware
- Five predictions recorded in the README before building begins

Also corrected two structural errors from the 28th: `calcs/README.md` held only
a 197-byte stub, and `build-log.md` had been created at `calcs/docs/` instead of
`docs/`.

**Next:** order Phase 1 parts (~$44, long lead time from AliExpress); source
rice cooker, wiper motor and ATX supply locally (~$29). Each of us to re-derive
the three calculations independently before parts arrive.

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
