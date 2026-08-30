# Prior art review

Searched before design work began, to establish what exists and where the gap
is. Conducted August 2026 across GitHub, Hackaday, Hackster, Instructables,
and the academic literature.

---

## Commercial products

| Product | Price | Approach |
|---|---|---|
| Lomi | ~$500 | Heat to 55–60 °C, rotating blade, airflow, carbon filter. Marketed with a microbial additive. |
| Vitamix FoodCycler | ~$400 | Heat, grind, dry. Closest in principle to this design. |
| Reencle | ~$500 | Inoculated warm digester held near 50 °C, continuous feed. Different process. |

All three are sealed products. Thermal design, airflow rates, and measured
specific energy consumption are not published for any of them.

**What we take from them:** the process sequence (macerate → heat → sweep →
mill) is validated by three independent commercial implementations. We are not
inventing the approach; we are documenting and measuring it.

---

## Open-source adjacent work

**Arduino composting monitors** — element14, Hackster, several university
projects. These instrument a compost bin with temperature, moisture, and gas
sensors. They *observe* decomposition; they do not accelerate it. Useful as
sensor-integration references, not as machine designs.

**Precision dehydrator controllers** — [truglodite/Dehydrator](https://github.com/truglodite/Dehydrator),
[qppd/Rice-Dryer](https://github.com/qppd/Rice-Dryer), and several ESP32-based
food dehydrator projects. These solve closed-loop thermal control well and are
directly applicable to our Phase 1 and Phase 4 work.

**Rice cooker / appliance hacking** — well documented, particularly for sous
vide. Establishes the SSR-switching-a-commercial-appliance pattern that our
safety analysis depends on.

---

## Academic literature

**Research on the drying kinetics of household food waste**
[PubMed 26507489](https://pubmed.ncbi.nlm.nih.gov/26507489/)

Findings we rely on:
- The Midilli model fits food waste drying data best across tested conditions
- Temperature dominates drying rate; air velocity has a smaller effect
- Total mass reduction up to 87% w/w is achievable with appropriate parameters

**Energy consumption of agricultural dryers: an overview**
[CIGR Journal](https://cigrjournal.org/index.php/Ejounral/article/download/3863/2494/0)

Establishes our efficiency benchmark: indirect drying equipment consumes
800–955 kWh per tonne of water evaporated, i.e. 0.80–0.96 kWh/kg. This is the
number our design is measured against.

**Thin-layer drying literature, general**

Most food materials dry predominantly in the *falling-rate* period, with a short
or entirely absent constant-rate period. This informs Prediction 4 and shapes
how we will annotate our own drying curves — we expect diffusion-limited
behaviour throughout, not a classical two-phase curve.

---

## The gap

We could not find an open-source project that documents a complete food waste
drying machine together with:

1. the sizing calculations that produced its geometry and component selection,
2. the firmware that runs it, and
3. measured performance data testing whether the calculations were right.

Each piece exists separately. The connection between them does not appear to be
published anywhere we could reach.

**This is stated as what our search found, not as an absolute claim.** If such a
project exists and we missed it, we would like to know — open an issue and we
will cite it here.

---

## What this means for our scope

Because the process is commercially validated, novelty is not our claim. Our
contribution is the *documentation*: predictions recorded before building,
measurements taken against them, and the discrepancies published either way.

That is a smaller claim than "we invented something." It is also one we can
actually support with data.
