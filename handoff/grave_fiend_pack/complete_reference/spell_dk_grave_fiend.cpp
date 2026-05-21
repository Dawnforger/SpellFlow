#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellInfo.h"
#include "Unit.h"

namespace GraveFiend
{
    static constexpr uint32 SPELL_GF_PASSIVE_AURA  = 91001;
    static constexpr uint32 SPELL_GF_OVERLOAD_AURA = 91002;
    static constexpr uint32 SPELL_GF_RUNE_ICD      = 91003;

    // Internal runic power units: 100 RP == 1000
    static constexpr int32 RP_ENTER_OVERLOAD = 2000;
    static constexpr int32 RP_EXIT_OVERLOAD  =  400;

    // Educational defaults (tune for your server)
    static constexpr int32 DRAIN_BASE_PER_SEC = 20; // 2 RP/s
    static constexpr int32 DRAIN_STEP_PER_SEC = 10; // +1 RP/s each tick
    static constexpr uint32 RUNE_ICD_MS       = 1000;

    bool IsRunicPowerGenerator(uint32 spellId)
    {
        switch (spellId)
        {
            // TODO: fill with exact RP-generating spell IDs on your branch.
            default:
                return false;
        }
    }

    bool IsRuneSpender(uint32 spellId)
    {
        switch (spellId)
        {
            // TODO: fill with exact rune-spender spell IDs on your branch.
            default:
                return false;
        }
    }

    bool IsBasicAttackProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        // White swings should not carry spell info.
        if (eventInfo.GetSpellInfo())
            return false;

        return true;
    }

    void RestoreRandomRune(Player* player)
    {
        if (!player)
            return;

        std::vector<uint8> depleted;
        for (uint8 rune = 0; rune < MAX_RUNES; ++rune)
        {
            if (player->GetRuneCooldown(rune))
                depleted.push_back(rune);
        }

        if (depleted.empty())
            return;

        uint8 selected = depleted[urand(0, depleted.size() - 1)];
        player->SetRuneCooldown(selected, 0);
    }
}

class spell_dk_grave_fiend_passive : public AuraScript
{
    PrepareAuraScript(spell_dk_grave_fiend_passive);

    void HandlePeriodic(AuraEffect const*)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32 rp = player->GetPower(POWER_RUNIC_POWER);

        if (rp >= GraveFiend::RP_ENTER_OVERLOAD && !player->HasAura(GraveFiend::SPELL_GF_OVERLOAD_AURA))
            player->CastSpell(player, GraveFiend::SPELL_GF_OVERLOAD_AURA, TRIGGERED_FULL_MASK);

        if (rp <= GraveFiend::RP_EXIT_OVERLOAD && player->HasAura(GraveFiend::SPELL_GF_OVERLOAD_AURA))
            player->RemoveAura(GraveFiend::SPELL_GF_OVERLOAD_AURA);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_dk_grave_fiend_passive::HandlePeriodic,
            EFFECT_0,
            SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_dk_grave_fiend_overload : public AuraScript
{
    PrepareAuraScript(spell_dk_grave_fiend_overload);

    uint8 _ticks = 0;

    void HandleApply(AuraEffect const*, AuraEffectHandleModes)
    {
        _ticks = 0;
    }

    void HandlePeriodic(AuraEffect const*)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        ++_ticks;
        int32 drain = GraveFiend::DRAIN_BASE_PER_SEC + int32(_ticks - 1) * GraveFiend::DRAIN_STEP_PER_SEC;
        player->ModifyPower(POWER_RUNIC_POWER, -drain);

        if (player->GetPower(POWER_RUNIC_POWER) <= GraveFiend::RP_EXIT_OVERLOAD)
            player->RemoveAura(GraveFiend::SPELL_GF_OVERLOAD_AURA);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return false;

        if (!GraveFiend::IsBasicAttackProc(eventInfo))
            return false;

        if (player->HasSpellCooldown(GraveFiend::SPELL_GF_RUNE_ICD))
            return false;

        return true;
    }

    void HandleProc(AuraEffect const*, ProcEventInfo&)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        GraveFiend::RestoreRandomRune(player);
        player->AddSpellCooldown(
            GraveFiend::SPELL_GF_RUNE_ICD,
            0,
            std::chrono::system_clock::now() + std::chrono::milliseconds(GraveFiend::RUNE_ICD_MS));
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_dk_grave_fiend_overload::HandleApply,
            EFFECT_0,
            SPELL_AURA_PERIODIC_DUMMY,
            AURA_EFFECT_HANDLE_REAL);

        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_dk_grave_fiend_overload::HandlePeriodic,
            EFFECT_0,
            SPELL_AURA_PERIODIC_DUMMY);

        DoCheckProc += AuraCheckProcFn(spell_dk_grave_fiend_overload::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_dk_grave_fiend_overload::HandleProc,
            EFFECT_0,
            SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_spell_dk_grave_fiend()
{
    RegisterAuraScript(spell_dk_grave_fiend_passive);
    RegisterAuraScript(spell_dk_grave_fiend_overload);
}
