# Conversation Handoff (Condensed)

Date context: 2026-05-21 UTC

## User goals across this chat

1. Asked for a basic step layout for creating custom spells/auras in AzerothCore.
2. Requested a practical implementation plan for a new DK glyph concept:
   - **Grave Fiend**
   - Max Runic Power increased to 200
   - At 200 RP, enter a special state:
     - escalating RP drain per second
     - RP-generating abilities: +75% damage and +75% RP generated
     - basic attacks restore a random rune (1s ICD)
     - rune spender GCD reduced by 50%
   - state ends at <= 40 RP
3. Requested educational skeleton packs and then a complete reference-style pack.
4. Asked whether a desktop generator/no-code helper is viable for mass ability production.
5. Requested packaging of this workflow for continuation in Cursor Desktop.

## Key design decisions established

- Implement as an aura-driven state machine:
  - Passive watcher aura
  - Overload aura (active state)
- Use SQL migrations (idempotent) for DBC-like spell data changes.
- Avoid manual .dbc editing.
- Keep spell classification explicit (RP generators vs rune spenders).
- Use script hooks for advanced behavior where DB-only auras are insufficient.

## Artifacts prepared in this repo

- `handoff/grave_fiend_pack/skeleton/*`
  - Fill-in templates for SQL + C++ + test plan
- `handoff/grave_fiend_pack/complete_reference/*`
  - Educational reference with concrete IDs and example logic
- `handoff/RESUME_PROMPT.md`
  - Copy/paste prompt to continue work in Cursor Desktop

## Known caveats to resolve in your actual implementation branch

- AzerothCore branch/table schema differences (especially `spell_dbc`, `spell_proc` columns).
- Exact script hooks for:
  - damage multiplier on RP generators
  - RP gain multiplier
  - GCD reduction on rune spenders
- Final spell ID lists for RP-generators and rune spenders should be explicit and validated.

## Recommended next step

Use the resume prompt and ask Cursor Desktop to map these templates to your exact AzerothCore fork schema/APIs before coding live server content.
