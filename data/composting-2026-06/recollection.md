# Composting programme, June–August 2026 — retrospective account

**The original notebook is lost.** No instrument records survive from this
period.

This document is written from recollection on 1 September 2026. It records what
was done and what was observed. It contains **no numeric measurements**, because
none can be recovered, and estimating them retrospectively would produce figures
indistinguishable from data while being nothing of the kind.

What follows is qualitative and is labelled as such. It should be read as
testimony, not as a dataset.

---

## What was done

Starting **12 June 2026**, food waste was collected from a restaurant and
composted to produce liquid fertiliser.

Batches ran **1 to 2.5 months** each. Temperature and process efficiency were
monitored throughout — the values were recorded at the time and are lost.

The process was managed by hand: collection, loading, turning, monitoring, and
drawing off the liquid product.

## What was observed

**The process worked.** Usable liquid fertiliser was produced from restaurant
food waste across multiple batches.

**Odour was the principal practical problem, and it was solved.** Early batches
smelled strongly. This was worked on deliberately across subsequent batches and
the odour was substantially reduced.

> The specific change responsible is not recorded. This is the single most
> significant loss in the missing notebook — it was a solved problem, and the
> solution is not written down. If any team member recalls what was altered
> between batches, add it here.

**The effort-to-output ratio was poor.** Months of sustained attention produced
a small quantity of fertiliser. The process required repeated manual
intervention and could not be left alone. It was inconvenient enough that no
household would sustain it, which is a finding about the *process*, not about
the biology.

## What followed from it

By mid-July the conclusion was that the limiting factor was not biological. The
decomposition worked. What made the process impractical was that the mechanical
work — breaking material down, holding it warm, moving air through it — was
being done by hand.

Machine construction began **15 July 2026**. See
[`../../docs/build-log.md`](../../docs/build-log.md).

## Still running

The liquid fertiliser from this programme is currently being tested on flowers
and vegetables. That trial is ongoing and, unlike the composting programme, it
can still be instrumented properly — protocol in
[`../../docs/germination-trial.md`](../../docs/germination-trial.md).

---

## Status of this record

| | |
|---|---|
| Qualitative account | Recorded here, from memory |
| Dates | Approximate, from memory |
| Temperature series | **Lost** |
| Yield and input masses | **Lost** |
| Odour scoring | **Lost** — only the direction of change is remembered |
| pH, if measured | **Unknown** |

### Recovery still worth attempting

Before treating this as final, check:

- **The other three team members' notes.** Four people ran this; one notebook
  is not necessarily the only record.
- **Phone photographs.** Images carry timestamps. A photo of a thermometer is a
  dated measurement.
- **Group chat history.** Messages reporting progress are timestamped
  contemporaneous records and are in some respects better evidence than a
  notebook.
- **Restaurant collection records.** May establish input quantities and dates.

Anything recovered goes into `batch-log.csv` with its source noted.

### The forward correction

Composting is repeatable, and the process is now better understood than it was
in June — the odour problem, whatever its solution was, was solved once.

**A new batch started now, logged from day one, produces real data in 4–8
weeks.** That is the answer to a lost notebook: not reconstruction, but
repetition under proper measurement. Schema is ready in
[`README.md`](./README.md).
