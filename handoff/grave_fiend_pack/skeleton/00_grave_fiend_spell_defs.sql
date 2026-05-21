-- Idempotent migration: base spell definitions for Grave Fiend.
-- Fill IDs and all schema-specific spell_dbc columns for your AzerothCore branch.

SET @GF_GLYPH_SPELL     := 0; -- TODO
SET @GF_PASSIVE_AURA    := 0; -- TODO
SET @GF_OVERLOAD_AURA   := 0; -- TODO
SET @GF_RUNE_ICD_SPELL  := 0; -- TODO

-- If your branch stores custom spell rows in spell_dbc:
-- 1) DELETE deterministic target IDs
-- 2) INSERT full rows for each custom spell
--
-- Example pattern:
-- DELETE FROM `spell_dbc`
-- WHERE `Id` IN (@GF_PASSIVE_AURA, @GF_OVERLOAD_AURA, @GF_RUNE_ICD_SPELL);
--
-- INSERT INTO `spell_dbc` ( `Id`, ... all required columns ... )
-- VALUES
-- (@GF_PASSIVE_AURA,  ... max RP + periodic watcher ...),
-- (@GF_OVERLOAD_AURA, ... periodic 1s drain controller ...),
-- (@GF_RUNE_ICD_SPELL, ... hidden internal cooldown marker ...);

-- Keep rerunnable. No direct .dbc file edits.
