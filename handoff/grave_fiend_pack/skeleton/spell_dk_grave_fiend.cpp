#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellInfo.h"

namespace GF
{
    static constexpr uint32 PASSIVE_AURA   = 0; // TODO
    static constexpr uint32 OVERLOAD_AURA  = 0; // TODO
    static constexpr uint32 RUNE_ICD_SPELL = 0; // TODO

    // Internal units: 100 RP == 1000
    static constexpr int32 RP_ENTER = 2000;
    static constexpr int32 RP_EXIT  =  400;

    static constexpr int32 DRAIN_BASE = 0; // TODO
    static constexpr int32 DRAIN_STEP = 0; // TODO
    static constexpr uint32 ICD_MS    = 1000;

    bool IsRPGenerator(SpellInfo const* /*spellInfo*/) { return false; } // TODO
    bool IsRuneSpender(SpellInfo const* /*spellInfo*/) { return false; } // TODO
    bool IsBasicAttackProc(ProcEventInfo& /*eventInfo*/) { return false; } // TODO
    void RestoreRandomRune(Player* /*player*/) {} // TODO
}

class spell_dk_grave_fiend_passive : public AuraScript
{
    PrepareAuraScript(spell_dk_grave_fiend_passive);

    void OnTick(AuraEffect const*)
    {
        // TODO:
        // - if RP >= 200 and overload missing -> apply overload
        // - if RP <= 40 and overload present -> remove overload
    }

    void Register() override
    {
        // TODO: match EFFECT index and aura type to spell data
        // OnEffectPeriodic += AuraEffectPeriodicFn(...);
    }
};

class spell_dk_grave_fiend_overload : public AuraScript
{
    PrepareAuraScript(spell_dk_grave_fiend_overload);
    uint8 _ticks = 0;

    void OnApply(AuraEffect const*, AuraEffectHandleModes) { _ticks = 0; }
    void OnTick(AuraEffect const*) { /* TODO: escalating drain + remove at <=40 RP */ }
    bool CheckProc(ProcEventInfo&) { return false; } // TODO
    void HandleProc(AuraEffect const*, ProcEventInfo&) { /* TODO */ }

    void Register() override
    {
        // TODO:
        // - periodic drain hook
        // - proc hook for basic attacks + ICD
        // - custom hooks for dmg/RP/GCD modifiers
    }
};

void AddSC_spell_dk_grave_fiend()
{
    RegisterAuraScript(spell_dk_grave_fiend_passive);
    RegisterAuraScript(spell_dk_grave_fiend_overload);
}
