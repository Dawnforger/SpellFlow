# Grave Fiend Educational Pack

This pack includes two variants:

## 1) `skeleton/`

Fill-in-yourself templates intended for learning and controlled implementation.

- `00_grave_fiend_spell_defs.sql`
- `01_grave_fiend_bindings.sql`
- `02_grave_fiend_proc_conditions.sql`
- `spell_dk_grave_fiend.cpp`
- `test_plan.md`

## 2) `complete_reference/`

A more complete educational reference with concrete sample IDs and working structure.

- `00_grave_fiend_spell_defs.sql`
- `01_grave_fiend_bindings.sql`
- `02_grave_fiend_proc_conditions.sql`
- `spell_dk_grave_fiend.cpp`
- `loader_snippet.txt`
- `test_plan.md`

## Core constraints

- Keep DBC-like edits in SQL migrations only.
- Ensure all migrations are idempotent.
- Expect branch-specific tuning for table columns/hook signatures.
