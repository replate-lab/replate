# Composting programme, June-August 2026

Restaurant food waste → liquid fertiliser. The work that preceded the machine
and established why one was needed.

---

## The programme

Starting **12 June 2026**, food waste was collected from a restaurant and
composted to produce liquid fertiliser. Batches ran **1 to 2.5 months** each,
managed by hand throughout: collection, loading, turning, monitoring, and
drawing off the liquid product.

## What it established

**The process works.** Usable liquid fertiliser was produced from restaurant
food waste across multiple batches.

**Odour was the principal practical problem, and it was solved.** Early batches
smelled strongly. This was worked on deliberately across subsequent batches and
the odour was substantially reduced.

**The effort-to-output ratio is poor.** Months of sustained attention produced
a small quantity of fertiliser. The process required repeated manual
intervention and could not be left alone, inconvenient enough that no
household would sustain it. This is a finding about the *process*, not about
the biology.

## What followed

By mid-July the conclusion was that the limiting factor was not biological. The
decomposition works. What makes the process impractical is that the mechanical
work, breaking material down, holding it warm, moving air through it, is done
by hand.

Machine construction began **15 July 2026**. See
[`../../docs/build-log.md`](../../docs/build-log.md).

## Still running

The liquid fertiliser from this programme is being tested on flowers and
vegetables. Protocol, control design, and the Zucconi maturity index:
[`../../docs/germination-trial.md`](../../docs/germination-trial.md).

---

## Logging standard

Batches from here on are logged to `batch-log.csv` in this directory, one row
per observation.

### Columns

| Column | Unit | Notes |
|---|---|---|
| `date` | YYYY-MM-DD | |
| `batch_id` |  | `B1`, `B2`, … one per composting run |
| `day` | days | Days since that batch started |
| `temp_c` | °C | State in `notes` whether surface or core |
| `ambient_c` | °C | |
| `input_kg` | kg | Waste added |
| `output_l` | L | Liquid fertiliser drawn off |
| `odour` | 0-5 | 0 = none, 5 = strong. One scorer per batch, for consistency |
| `ph` |  | |
| `notes` | text | Turning, additions, weather, any change in smell |

If we did not measure something, leave the cell **empty** instead of guessing.
A blank tells the next person there is nothing there. A made-up number does not.

### Per batch, also record

```
Batch ID:
Start date:
End date:
Waste source and rough composition:
Total input mass:
Total liquid output:
Container type and volume:
Additions (bulking agent, water, inoculum):
Turning frequency:
Where kept (indoor/outdoor, temperature range):
What we changed from the previous batch:
```

That last line carries the most weight. Improvements between batches, the
odour reduction being the clearest example, only become transferable results
if the change responsible is written down.

### Template

Save as `batch-log.csv`:

```csv
date,batch_id,day,temp_c,ambient_c,input_kg,output_l,odour,ph,notes
```

---

## Running the manual process alongside the machine

The most valuable measurement available to this project is a **direct
comparison**: the same restaurant waste, the same week, processed by hand and
by machine, both logged.

That gives a like-for-like figure for time, effort, and output, the claim the
whole project rests on, measured rather than asserted. Worth starting a batch
for that purpose alone.
