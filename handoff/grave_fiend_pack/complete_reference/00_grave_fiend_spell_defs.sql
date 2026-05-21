-- Grave Fiend complete reference (educational).
-- DBC-like data must be handled in SQL migration, never manual .dbc editing.
-- IDs below are example custom IDs; adjust to your server policy.

SET @GF_GLYPH_SPELL     := 91000;
SET @GF_PASSIVE_AURA    := 91001;
SET @GF_OVERLOAD_AURA   := 91002;
SET @GF_RUNE_ICD_SPELL  := 91003;

-- IMPORTANT:
-- `spell_dbc` schemas differ by branch. Use your full required column list.
-- Keep deterministic and idempotent:
--
-- DELETE FROM `spell_dbc`
-- WHERE `Id` IN (@GF_PASSIVE_AURA, @GF_OVERLOAD_AURA, @GF_RUNE_ICD_SPELL);
--
-- INSERT INTO `spell_dbc` (`Id`, ... all required columns ...)
-- VALUES
-- (@GF_PASSIVE_AURA,  ... max RP increase + periodic watcher ...),
-- (@GF_OVERLOAD_AURA, ... periodic 1s dummy for drain/proc control ...),
-- (@GF_RUNE_ICD_SPELL, ... hidden internal cooldown marker ...);
