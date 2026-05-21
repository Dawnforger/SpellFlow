-- Grave Fiend link + script bindings (idempotent reference)

SET @GF_GLYPH_SPELL     := 91000;
SET @GF_PASSIVE_AURA    := 91001;
SET @GF_OVERLOAD_AURA   := 91002;

DELETE FROM `spell_linked_spell`
WHERE `spell_trigger` = @GF_GLYPH_SPELL
  AND `spell_effect` = @GF_PASSIVE_AURA;

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (@GF_GLYPH_SPELL, @GF_PASSIVE_AURA, 0, 'Grave Fiend: glyph grants passive aura');

DELETE FROM `spell_script_names`
WHERE (`spell_id` = @GF_PASSIVE_AURA  AND `ScriptName` = 'spell_dk_grave_fiend_passive')
   OR (`spell_id` = @GF_OVERLOAD_AURA AND `ScriptName` = 'spell_dk_grave_fiend_overload');

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(@GF_PASSIVE_AURA,  'spell_dk_grave_fiend_passive'),
(@GF_OVERLOAD_AURA, 'spell_dk_grave_fiend_overload');
