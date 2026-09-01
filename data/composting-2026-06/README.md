# Composting data, June–August 2026

Restaurant food waste → liquid fertiliser. Batches of 1–2.5 months. Temperature
and yield tracked; odour reduction worked on deliberately and achieved.

**This data exists in personal notes and has not been transcribed yet.**

It is not reconstructed here, and it will not be estimated. Numbers in this
directory come from the notebook or they do not appear. A gap that is labelled
is recoverable; an invented figure that later gets quoted is not.

---

## What to transcribe

Fill [`batch-log.csv`](./batch-log.csv) from the notebook. Copy the template
below into a new file of that name and add one row per observation.

If a field was not recorded, leave it **empty**. Do not guess and do not
interpolate — an empty cell is information, a plausible-looking invented number
is not.

### Columns

| Column | Unit | Notes |
|---|---|---|
| `date` | YYYY-MM-DD | Approximate is fine; mark it in `notes` |
| `batch_id` | — | `B1`, `B2`, … one per composting run |
| `day` | days | Days since that batch started |
| `temp_c` | °C | Where measured — surface or core? Say which in `notes` |
| `ambient_c` | °C | If recorded |
| `input_kg` | kg | Waste added, cumulative or that day |
| `output_l` | L | Liquid fertiliser drawn off |
| `odour` | 0–5 | 0 = none, 5 = strong. Whoever scored it, be consistent |
| `ph` | — | If measured |
| `notes` | text | Anything unusual — turning, additions, weather, smell change |

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

That last line is the most valuable one. The odour reduction happened because
something was changed between batches — recording *what* turns a two-month
effort into a result.

---

## Why this matters more than it looks

Two months of temperature data across multiple batches is a real dataset. Very
few student projects have anything comparable, and it does three things the
machine work cannot:

1. **It establishes the baseline the machine is compared against.** "The machine
   is faster" is an assertion until there is a number for how long the manual
   process took.
2. **It is the evidence for the pivot.** The README argues that composting
   worked but cost too much effort for too little output. This data is what
   supports that claim.
3. **It is prior art we generated ourselves.** The odour reduction in particular
   — that was a solved problem, and the solution is worth writing down.

---

## Template

Save as `batch-log.csv` in this directory:

```csv
date,batch_id,day,temp_c,ambient_c,input_kg,output_l,odour,ph,notes
```

Header only. Add rows from the notebook.
