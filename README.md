# re:plate

An open-source benchtop machine that dries and grinds household food waste
into a stable, storable soil amendment feedstock in under five hours.

**Status:** Phase 0 — design and calculation. Nothing is built yet.
**Budget:** $225 USD, all-in.

---

## Why this repository exists

Commercial food recyclers — Lomi, Vitamix FoodCycler, Reencle — cost $400–600
and ship as closed boxes. Plenty of Arduino compost *monitors* exist. Several
good precision dehydrator controllers exist.

But I could not find a single open-source project that documents a complete
food waste drying machine: the mechanical design, the sizing calculations, and
the measured performance data, together, in one place.

So I am building one and publishing all of it — including the parts that don't work.

## What it does, and what it does not

**It does not produce finished compost.** Anyone claiming a five-hour machine
makes compost is overstating it.

What comes out is dried, ground, odourless, volume-reduced organic material —
stable enough to store for months. It becomes actual compost after 2–4 weeks
of curing in soil or a compost bin, which needs no machine at all.

```
food waste
  → [ re:plate — 5 hours ]     → dried feedstock
  → [ cure bin — 3 weeks ]     → compost
```

This machine is stage one. I am precise about that boundary because the
engineering claim I am making is thermal and mechanical, not biological.

## The engineering thesis

**This machine is fundamentally a dryer.** About 75% of food waste by mass is
water, and removing it dominates the entire energy budget. Everything else —
the heater sizing, the blower, the insulation, the control loop — follows from
that one fact.

The central design problem is that drying is **limited by mass transfer, not
just heat**. Airflow has to physically carry water vapour out of the vessel,
but that same airflow carries heat out too. More air dries faster and costs
more energy per kilogram of water removed. Less air conserves heat and stalls
the drying.

There is a real optimum. It is specific to this machine's geometry, and it
cannot be calculated from first principles — it has to be measured. Finding
it is the point of this project.

## Design targets

| Parameter | Target |
|---|---|
| Batch capacity | 1.0 kg wet waste |
| Cycle time | 4–5 hours |
| Energy per cycle | 0.82 kWh |
| Specific energy | 1.21 kWh per kg water removed |
| Mass reduction | ~65% |
| Heater | 400 W, duty-cycled |
| Airflow | 150 L/min, PWM-adjustable |
| Mixing torque | 2.7 N·m design, 12 N·m motor |

For reference: industrial indirect dryers achieve 0.80–0.96 kWh/kg water. The
theoretical floor set by the latent heat of vaporization is 0.67. Starting at
1.21 and driving it down is the optimisation target.

## What I am measuring

The machine is instrumented to produce data, not just output:

- **Load cell under the vessel** → mass vs. time, logged at 0.2 Hz. This gives
  the drying curve directly.
- **Two thermocouples** (core, exhaust) → thermal behaviour and loss estimation.
- **Inlet and exhaust humidity** → actual moisture pickup vs. the predicted 0.084 kg/kg.
- **Motor current** → mixing torque vs. moisture content. I expect a mid-cycle
  peak when the material is dough-like, higher than at either wet or dry extremes.

Planned outputs: drying curves across conditions, the energy-vs-airflow
optimisation plot, and a torque-vs-moisture curve.

## Honest accounting

At roughly 0.8 kWh per kilogram of waste, on a coal-heavy grid this machine
emits about as much CO₂ as landfilling the same waste would. That is not a
comfortable result and I am not going to bury it.

Two things follow. First, the machine's real use case is apartments, where the
alternative is landfill rather than a compost pile. Second, it means the
efficiency work has actual stakes — getting specific energy from 1.21 to below
0.9 kWh/kg is what makes the machine defensible. A counterflow exhaust heat
exchanger is the planned route there.

I will publish the lifecycle numbers either way.

## Repository structure

```
/calcs        — sizing calculations, worked with stated assumptions
/cad          — Fusion 360 models, drawings, exports
/firmware     — ESP32 controller
/data         — raw logs from every run, including failed ones
/docs         — build log, wiring, bill of materials
```

## Build phases

- [ ] **Phase 0** — Calculations and specification
- [ ] **Phase 1** — Thermal test rig (no motor, no blower) → first drying curve
- [ ] **Phase 2** — Airflow and exhaust → energy-vs-airflow optimum
- [ ] **Phase 3** — Agitation → torque characterisation
- [ ] **Phase 4** — Integration and closed-loop control
- [ ] **Phase 5** — Characterisation and repeat testing
- [ ] **Phase 6** — Heat recovery (stretch)

Each phase ends at a measurable gate. I do not start the next one until the
gate passes.

## Safety

This machine combines mains voltage, sustained heat, steam, and a powered
blade. The heating element is not hand-wired — it is a commercial appliance
switched by an SSR, so its factory thermal protection stays intact. There is
an independent non-resettable thermal fuse, an RCD on the supply, and a
hardware lid interlock on the motor.

Full notes in `/docs/safety.md`. If you build from this, read them first.

## License

Apache 2.0 for firmware. Documentation under CC BY-SA 4.0. Hardware designs
under CERN-OHL-S v2.

---

*Built in Ulaanbaatar, Mongolia. This is a student project and a first
prototype — expect it to be wrong in places, and expect me to say so when it is.*
