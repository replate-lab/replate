# CAD

**Lead:** Tsenguun Battulga
**Status:** empty. v1 was built without CAD; v2 is not.

---

## What belongs here

| File | Purpose |
|---|---|
| `v2-assembly.f3d` | Full assembly, Fusion 360 native |
| `v2-assembly.step` | Neutral format, openable without Fusion, and still readable in ten years |
| `v2-exploded.png` | Exploded view render |
| `v2-section.png` | Section through the vessel showing blade clearance and the shaft seal |
| `drawings/blade.pdf` | Dimensioned manufacturing drawing |
| `drawings/*.dxf` | Flat profiles for laser or waterjet cutting |

Commit the STEP alongside the `.f3d`. A Fusion file is only useful to someone
with Fusion and the right version; STEP is readable by everything.

---

## The one drawing that has to be right

The blade. It is the only part being sent out for manufacture, so it is the
only part where a drawing is the deliverable rather than a description.

It is better to do one drawing properly than ten of them casually. It
should carry:

- Overall dimensions with tolerances
- Hole positions and diameters, with tolerances
- Material and thickness specified
- Surface finish where it matters
- Bend lines, if any, with internal radius
- Title block: part name, material, quantity, scale, date, drawn by

This is also the drawing that goes in the portfolio. Readers who know
mechanical engineering will look at exactly this and judge whether the
dimensioning scheme makes sense, whether datums are sensible, whether
tolerances are specified where function requires them rather than everywhere.

Send the DXF to the shop; keep the PDF here as the record of what was
specified.

---

## Sections worth modelling carefully

Three areas are where geometry decisions actually get made, rather than just
recorded:

**Blade tip clearance to the vessel wall.** Too tight and it jams on a hard
inclusion; too loose and material packs against the wall unmixed. Section view
makes this a decision instead of an accident.

**Shaft penetration and seal.** We think this is the first thing that will break,
which is Prediction 5 in the main README. It has to survive heat, moisture and
abrasive solids all at once. Model it properly.

**Airflow path.** Inlet, headspace, exhaust. The mass-transfer argument in
`/calcs` assumes air actually sweeps the surface rather than short-circuiting
from inlet to outlet. Geometry decides whether that assumption holds.

---

## v1

v1 was built without CAD, which is a normal way to start and not worth
apologising for. Its as-built dimensions are recorded in
[`../docs/v1/specs.md`](../docs/v1/specs.md) instead.

Going back and modelling v1 from those measurements would be worth doing. It
would give us a direct geometric comparison against v2, and it is good practice
on a machine that already exists.
