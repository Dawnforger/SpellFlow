# Resume Prompt for Cursor Desktop

Use this prompt in Cursor Desktop chat:

---

I am resuming work from a cloud-agent handoff. Please continue from the packaged context in this repo:

- `handoff/CONVERSATION_HANDOFF.md`
- `handoff/grave_fiend_pack/README.md`
- `handoff/grave_fiend_pack/skeleton/*`
- `handoff/grave_fiend_pack/complete_reference/*`

Objectives for this session:

1. Validate that the SQL migrations are fully idempotent for my AzerothCore schema.
2. Adapt the C++ scripts to my exact core branch APIs/hook signatures.
3. Build finalized spell classification lists:
   - RP-generating abilities
   - Rune spenders
4. Produce a final production-ready version while preserving educational comments.
5. Keep all DBC-like modifications in SQL migration files only (no direct .dbc editing).

Please begin by reading the handoff files and giving me:
- a branch-specific compatibility check
- a patch plan
- then the first implementation commit.

---
