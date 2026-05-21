-- Optional idempotent proc/condition migration.
-- Fill exact schema and entries for your branch.

SET @GF_OVERLOAD_AURA := 0; -- TODO

-- Example shape:
-- DELETE FROM `spell_proc` WHERE `SpellId` = @GF_OVERLOAD_AURA;
-- INSERT INTO `spell_proc` ( ... columns ... ) VALUES ( ... );

-- Optional class/spec gating:
-- DELETE FROM `conditions` WHERE ...;
-- INSERT INTO `conditions` (...) VALUES (...);
