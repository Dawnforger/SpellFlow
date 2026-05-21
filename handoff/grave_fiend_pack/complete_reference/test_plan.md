# Grave Fiend Test Plan (Complete Reference)

## Setup

1. Learn/apply glyph spell.
2. Confirm passive aura is present.
3. Confirm max Runic Power is 200.

## Core behavior checks

1. Build RP to 200; verify overload aura applies.
2. Track RP over time; verify per-second drain and increasing drain amount.
3. Verify overload is removed when RP <= 40.

## Bonus behavior checks

1. RP-generating ability baseline:
   - record damage
   - record RP gained
2. Repeat during overload:
   - damage should be +75%
   - RP generation should be +75%
3. Perform repeated white swings:
   - depleted runes should restore randomly
   - never restore more than once each 1s
4. Cast rune spenders during overload:
   - GCD should be reduced by 50%
5. Confirm all bonuses stop after overload ends.

## Edge cases

- Relog while overload is active
- Death/ressurection transitions
- Instance or map transfer
- PvE and PvP target variance
- High latency burst casts near RP threshold boundaries
