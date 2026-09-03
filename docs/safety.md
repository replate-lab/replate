# Safety analysis

This machine combines four independently dangerous elements: mains voltage,
sustained heat, steam, and a powered blade. Each mitigation below is a
requirement, not a recommendation.

**Read this before building or modifying anything.**

---

## Hazard register

| # | Hazard | Consequence | Mitigation | Independent of firmware? |
|---|---|---|---|---|
| H1 | Mains contact | Electrocution | Heater is a sealed commercial appliance; mains section in its own earthed enclosure; line fused | ✅ |
| H2 | Earth fault through wet mass | Electrocution | RCD / GFCI on supply | ✅ |
| H3 | Thermal runaway | Fire | 120 °C non-resettable thermal fuse in series with heater | ✅ |
| H4 | Controller failure with heater on | Fire | H3 above; plus firmware over-temperature abort as a second layer | Partly |
| H5 | Blade contact | Severe hand injury | Hardware lid interlock switch cutting motor power | ✅ |
| H6 | Steam burn | Scald | Vent routed away from the operator; no opening above 60 °C core | ❌ |
| H7 | Vent blockage | Pressure build-up | Vessel unsealed by design; filter checked for condensate loading | ❌ |
| H8 | Motor jam under load | Motor burnout, fire | Current sensing with auto-reverse; motor thermal fuse | Partly |

The right-hand column matters most. **Any mitigation that depends on software
is not a safety system.** Software fails, and this is a first firmware written
by a first-time team. H1, H2, H3, and H5 are all handled in hardware and would
still function with the ESP32 removed entirely.

---

## The heater decision

The single most hazardous fabrication step in a machine like this is wiring a
mains heating element by hand. We do not do it.

A used rice cooker is purchased whole and switched on its mains cord by a
solid-state relay. This preserves the appliance's factory thermal cut-out,
insulation, and earthing, protection engineered and type-tested by a
manufacturer, which we cannot reproduce.

The SSR switches the appliance. It does not replace anything inside it.

---

## Wiring rules

1. **Physical separation.** Mains section (SSR, appliance cord, fusing) lives in
   its own earthed enclosure, separated from the low-voltage electronics. No
   mains conductor shares a cable route or terminal block with signal wiring.

2. **Bond metalwork to earth.** Vessel and frame both bonded. Verify continuity
   with a multimeter before first power-on.

3. **Fuse the line** at the supply, ahead of everything.

4. **Thermal fuse is series-wired to the heater**, not to the controller. It
   must open the heater circuit regardless of what any code is doing.

5. **Lid interlock is a hardware switch** in the motor supply, not a GPIO read.
   Firmware also checks it, as a second layer, but the switch is the safety
   system.

---

## Operating rules

- **Never run unattended** until twenty logged, uneventful cycles are recorded
  in the build log. Not "it seems fine", twenty logged cycles.
- **Never open the lid above 60 °C** core temperature. Steam.
- **Never bypass the interlock** to observe the blade running. There is no
  observation worth a hand.
- **First power-on:** one person present at the disconnect switch, eye
  protection on, extinguisher within reach.
- **Confirm the vent path is clear** before every run. The carbon filter loads
  with condensate over time and must be inspected.

---

## Team responsibility

If any team member is under 18 or working unsupervised, an adult with mains
wiring experience must inspect the electrical work before first power-on. This
is not optional and it is not a formality.

Every safety-relevant modification is recorded in `build-log.md` with the date
and who made it.
