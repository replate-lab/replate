# Germination trial protocol

The liquid fertiliser produced during the June–August composting work is
currently being tested on flowers and vegetables. This document specifies how
that test should be run so the result means something.

**Status:** protocol written 2026-09-01. Trial in progress — if it is already
running without a control, start a parallel run using this design.

---

## What is actually being tested

Not "does the fertiliser help plants grow." The real question is narrower and
more important:

> **Is the compost mature, or is it phytotoxic?**

Immature compost contains ammonia, organic acids, and soluble salts that
actively inhibit germination. A fertiliser that looks and smells finished can
still suppress seedlings. This is the standard failure mode and it is exactly
what a germination assay detects.

Answering it also tells us something about the machine: if the dried output from
re:plate needs a shorter cure than hand-composted material to reach the same
maturity, that is a real, measurable claim about the process.

---

## Design

### Groups

Minimum four, run simultaneously:

| Group | Treatment | Purpose |
|---|---|---|
| **C** | Distilled water | Negative control — the baseline everything is scored against |
| **T10** | Fertiliser diluted 1:10 | Strong dose — most likely to show phytotoxicity |
| **T20** | Fertiliser diluted 1:20 | Moderate dose |
| **T50** | Fertiliser diluted 1:50 | Weak dose |

A commercial fertiliser at manufacturer-recommended dilution can be added as a
positive benchmark. Useful, not required.

### Replication

- **n ≥ 20 seeds per group**, split across at least **3 separate dishes or pots**
- Three replicates is the minimum that lets you state a spread rather than a
  single number
- One dish of 20 seeds is *not* three replicates

### Constants

Everything except the treatment must be identical:

- Same seed batch, same packet, same day
- Same substrate (filter paper for the assay; identical soil mix for pots)
- Same liquid volume per dish, measured, not poured by eye
- Same location, same light
- **Rotate dish positions daily.** A light or temperature gradient across a
  windowsill will produce a clean-looking result that is entirely an artefact of
  position. This is the single most common way a trial like this goes wrong.

---

## The measurement: Zucconi Germination Index

This is the accepted standard for compost maturity, which makes the result
comparable to published work rather than only to itself.

Run on filter paper in petri dishes — faster and cleaner than pots, and it is
what the index is defined for.

**Procedure**

1. Filter paper in each dish, 20 seeds evenly spaced
2. Add a measured volume of treatment solution (same volume in every dish)
3. Dark, 25 °C, 48–72 hours
4. Count germinated seeds
5. Measure root length of every germinated seed, in mm

**Calculation**

```
GI = ( G_treatment / G_control ) × ( L_treatment / L_control ) × 100

  G = number of seeds germinated
  L = mean root length
```

**Interpretation**

| GI | Meaning |
|---|---|
| < 50% | Strongly phytotoxic — not usable |
| 50–80% | Immature — needs further curing |
| **> 80%** | **Mature, non-phytotoxic** |
| > 100% | Growth stimulation beyond the control |

Cress, radish, or Chinese cabbage are the conventional test species — fast,
sensitive, and comparable to the literature. Use one of those for the index,
and run the flowers and vegetables separately as a practical demonstration.

---

## Pot trial (the longer, more visual test)

Run alongside the assay for photographs and growth data.

**Measure**
- Germination count at days 7, 10, 14
- Seedling height at days 14, 21 — mm, with a ruler in the photograph
- Leaf count at day 21
- Dry biomass at the end: harvest, dry at 70 °C to constant mass, weigh

Dry biomass is the most honest single number. Height can mislead — etiolated
seedlings stretch when stressed.

**Photograph daily**
- Same distance, same lighting, same angle
- Ruler in frame
- Written label visible: group, date
- One photo of all groups together each day — that is the comparison shot

---

## Record for every trial

```
Trial ID:
Start date:
Seed species and batch:
Substrate:
Fertiliser batch (which composting run, what date):
Dilutions used:
Volume per dish/pot:
Ambient temperature range:
Light: hours/day, source
Position rotation: yes/no, schedule
Scored by:
```

Anything not recorded here cannot be reconstructed later. The fertiliser batch
matters most — a result is meaningless if we cannot say which compost run
produced the material.

---

## Reporting

Report the GI with its spread across replicates, not a bare number. State
sample size. If a group failed or was contaminated, report that too — a trial
with one bad dish and an honest note is worth more than a clean number with an
unexplained gap.

Raw counts and measurements go in [`/data`](../data), not just the summary.
