-- Grave Fiend optional proc/condition reference.
-- Leave logic mostly in C++ when branch compatibility is uncertain.

SET @GF_GLYPH_SPELL     := 91000;
SET @GF_PASSIVE_AURA    := 91001;
SET @GF_OVERLOAD_AURA   := 91002;

-- Optional class/spec guards via conditions table:
-- DELETE FROM `conditions` WHERE ... SourceEntry IN (@GF_GLYPH_SPELL, @GF_PASSIVE_AURA, @GF_OVERLOAD_AURA);
-- INSERT INTO `conditions` (...) VALUES (...);

-- Optional spell_proc row if you prefer DB proc masks over script-side checks:
-- DELETE FROM `spell_proc` WHERE `SpellId` = @GF_OVERLOAD_AURA;
-- INSERT INTO `spell_proc` (...exact branch columns...) VALUES (...);
