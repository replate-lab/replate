# Prototype v1 — documentation

v1 exists and runs. This directory is where the evidence for that lives:
photographs, dimensions, and the wiring as actually built.

**Status:** awaiting capture. Nothing in here yet.

---

## Why this matters more than it sounds

Every analytical claim in this repository — the energy balance, the three
faults, the case for a smaller vessel — refers to a machine a reader cannot
see. Analysis without an object attached to it reads as speculation, however
carefully it is argued.

One afternoon of photography and measurement converts the whole repository from
a proposal into a record of something real.

---

## Shot list

Phone camera is fine. Daylight near a window, no flash. Wipe the lens first —
it makes more difference than anything else.

### The machine

| # | Shot | Why |
|---|---|---|
| 1 | Full machine, front, level with it | The establishing image. This is what goes at the top of the README. |
| 2 | Full machine, 3/4 angle | Shows depth and construction |
| 3 | Full machine with a ruler or a familiar object beside it | Scale. "Medium but too big" needs to be visible, since it is one of the three faults. |
| 4 | Lid open, looking down into the vessel | Blade geometry, vessel proportions |
| 5 | Blade assembly close up | The part with the torque problem |
| 6 | Heater as installed | The part with the overheating problem |
| 7 | Fan and air path | The part the mass-transfer argument is about |
| 8 | Motor and drive | Sizing evidence |
| 9 | Electrical connections as built | Honest record, including anything that needs improving |

### Running

| # | Shot | Why |
|---|---|---|
| 10 | Machine running, lid closed | Proof of operation |
| 11 | Load going in — weigh it first and note the mass | Input condition |
| 12 | Output at end of cycle, same framing | The result |
| 13 | Input and output side by side, same scale, ruler in frame | **The single most persuasive image in the project** |

### Anything that failed

| # | Shot | Why |
|---|---|---|
| 14 | Scorching, wear, deformation, anything that broke | Fault evidence. Do not tidy up before photographing. |

Shot 14 is worth more than shots 1–13 combined to a reader who knows hardware.
Everyone photographs the clean version. Almost nobody photographs the burnt bit.

---

## Naming

```
v1_01_front.jpg
v1_04_vessel-open.jpg
v1_13_input-output.jpg
v1_14_scorching-heater.jpg
```

Keep them under about 1 MB each — resize to roughly 1600 px on the long edge.
Git handles text well and binaries poorly.

---

## Measurements to record

Fill in [`specs.md`](./specs.md) while the machine is in front of you. These
numbers are needed to compare v1 against the v2 design point, and guessing them
later is not the same thing.

- Vessel internal diameter and height
- Vessel material and wall thickness
- Working volume, and typical batch mass actually processed
- Heater rating (from its label) and how it is switched
- Motor type and rated speed
- Fan type and rough airflow
- Insulation, if any
- Overall external dimensions and mass
- Typical cycle time as run
- Mains supply arrangement

## Wiring as built

A hand-drawn diagram, photographed, is entirely acceptable. What matters is
that it reflects what is actually wired, including anything provisional.

This also feeds [`../safety.md`](../safety.md) — the hazard register describes
v2's intended protections, and v1's real state should be recorded honestly
against it.
