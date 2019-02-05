#include "Includes.hxx"
#include "Lib.hxx"
#include "Hooking.hxx"

#ifndef _DEBUG
#pragma comment(lib,"..\\x64\\Release\\Detour.lib")
#else
#pragma comment(lib,"..\\x64\\Debug\\Detour.lib")
#endif

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

N_Hook::DetourFunction *D_Unknown = nullptr;
N_Hook::DetourFunction *D_Unknown2 = nullptr;
N_Hook::DetourFunction *D_Unknown3 = nullptr;
N_Hook::DetourFunction *D_Unknown4 = nullptr;
N_Hook::DetourFunction *D_Unknown5 = nullptr;
N_Hook::DetourFunction *D_Unknown6 = nullptr;

struct S_Routine
{
    S_Routine( Pointer pModule , bool bManualMapped = false )
    {
        this->pModule = pModule;
        this->bManualMapped = bManualMapped;
    }

    ~S_Routine()
    {
        pModule = nullptr;
        bManualMapped = false;
    }

    Pointer pModule;
    bool bManualMapped;
};

char *ItemTables[]
{
    "none",
    "item_rec_S",
    "item_rec_M",
    "item_rec_L",
    "item_rec_All",
    "item_recSt_Drk",
    "item_recSt_Hrg",
    "item_recSt_Ctrl",
    "item_recSt_All",
    "item_recAll",
    "item_recSt_Elc",
    "item_stUp_pAtk_S",
    "item_stUp_pAtk_M",
    "item_stUp_sAtk_S",
    "item_stUp_sAtk_M",
    "item_stUp_pDef_S",
    "item_stUp_pDef_M",
    "item_stUp_sDef_S",
    "item_stUp_sDef_M",
    "item_enCostDown_S",
    "item_enCostDown_M",
    "item_sprAmr_S",
    "item_sprAmr_M",
    "item_sprDash_S",
    "item_sprDash_M",
    "item_liquor",
    "item_feed_S",
    "item_goldUp_S",
    "item_goldUp_M",
    "item_dragA",
    "item_fruits",
    "weapon_japanese_sword",
    "weapon_pipe",
    "weapon_beastbain",
    "weapon_phoenix_dagger",
    "weapon_ancient_overload",
    "weapon_sf_sword",
    "weapon_uncouth_sword",
    "weapon_white_sword",
    "weapon_black_sword",
    "weapon_yoruha_sword",
    "weapon_robo_sword",
    "weapon_iron_will",
    "weapon_fang_of_the_twins",
    "weapon_beastlord",
    "weapon_phoenix_sword",
    "weapon_sf_large_sword",
    "weapon_uncouth_large_sword",
    "weapon_white_large_sword",
    "weapon_black_large_sword",
    "weapon_robo_axe",
    "weapon_phoenix_spear",
    "weapon_beastcurse",
    "weapon_dragon_lance",
    "weapon_spear_of_the_usurper",
    "weapon_sf_lance",
    "weapon_uncouth_lance",
    "weapon_white_lance",
    "weapon_black_lance",
    "weapon_robo_lance",
    "weapon_angel_combat",
    "weapon_devil_combat",
    "weapon_sf_combat",
    "weapon_uncouth_combat",
    "weapon_white_combat",
    "weapon_black_combat",
    "weapon_robo_arm",
    "weapon_ff_sword",
    "weapon_dq_sword",
    "weapon_dlc_combat",
    "item_mt_ore_S",
    "item_mt_ore_M",
    "item_mt_ore_L",
    "item_mt_ore_LL",
    "item_mt_mass_S",
    "item_mt_plate_S",
    "item_mt_alloy_S",
    "item_mt_alloy_M",
    "item_mt_fell",
    "item_mt_mainspring_S",
    "item_mt_wire_S",
    "item_mt_coil_S",
    "item_mt_circuit_S",
    "item_mt_screw_S",
    "item_mt_screw_M",
    "item_mt_gear_S",
    "item_mt_gear_M",
    "item_mt_bolt_S",
    "item_mt_bolt_M",
    "item_mt_nats_S",
    "item_mt_nats_M",
    "item_mt_socket_S",
    "item_mt_socket_M",
    "item_mt_cable_S",
    "item_mt_cable_M",
    "item_mt_battery_S",
    "item_mt_battery_M",
    "item_mt_roboArm",
    "item_mt_roboLeg",
    "item_mt_roboBody",
    "item_mt_roboHead",
    "item_mt_crystal",
    "item_mt_pearl",
    "item_mt_blackPearl",
    "item_mt_pyrite",
    "item_mt_amber",
    "item_mt_moldavite",
    "item_mt_meteorite",
    "item_mt_mass_M",
    "item_mt_machine_S",
    "item_mt_machine_M",
    "item_mt_machine_L",
    "item_mt_refine_S",
    "item_mt_refine_M",
    "item_mt_refine_L",
    "item_mt_nuts",
    "item_mt_seed",
    "item_mt_sap",
    "item_mt_mushroom",
    "item_mt_eagleEgg",
    "item_mt_bigEgg",
    "item_mt_book",
    "item_mt_technicalBook",
    "item_mt_dictionary",
    "item_mt_water",
    "item_mt_tanningAgent",
    "item_mt_dye",
    "item_mt_rubber",
    "item_mt_oil",
    "item_mt_fillerMetal",
    "item_mt_meat_deer",
    "item_mt_meat_boar",
    "item_mt_meat_Adeer",
    "item_mt_meat_Aboar",
    "item_mt_earrings",
    "item_mt_bracelet",
    "item_mt_choker",
    "item_mt_pierce",
    "item_mt_rose",
    "item_mt_mask",
    "item_mt_blackBox",
    "item_mt_blackBox_pascal",
    "item_mt_blackBox_children",
    "item_mt_pascalBook",
    "item_uq_mallKey",
    "item_uq_philosophyBook",
    "item_uq_filter",
    "item_uq_oil",
    "item_uq_accessKey_1",
    "item_uq_accessKey_2",
    "item_uq_accessKey_3",
    "item_uq_q121_musicBox",
    "item_uq_q020_letter",
    "item_uq_q020_glass",
    "item_uq_q020_fossil",
    "item_uq_sartre_letter",
    "item_uq_q140_memoryChip",
    "item_uq_q140_diary",
    "item_uq_q123_dataChip_A",
    "item_uq_q123_dataChip_B",
    "item_uq_q123_dataChip_C",
    "item_uq_q123_dataChip_D",
    "item_uq_q123_dataChip_E",
    "item_uq_q340_photo_1",
    "item_uq_q340_photo_2",
    "item_uq_q340_photo_3",
    "item_uq_q650_q651_importantThing",
    "item_uq_q181_to21O_1",
    "item_uq_q181_to21O_2",
    "item_uq_q181_to21O_3",
    "item_uq_q290_3colorCable_A",
    "item_uq_q291_3colorCable_B",
    "item_uq_q292_3colorCable_C",
    "item_uq_q071_sundryGoods_1",
    "item_uq_q071_sundryGoods_2",
    "item_uq_q071_sundryGoods_3",
    "item_uq_q071_sundryGoods_4",
    "item_uq_q071_sundryGoods_5",
    "item_uq_q440_roboParts",
    "item_uq_q660_stamp",
    "item_uq_q660_stampCard",
    "item_uq_q590_heritage_1",
    "item_uq_q590_heritage_2",
    "item_uq_q590_heritage_3",
    "item_uq_q590_heritage_4",
    "item_uq_pascalReq_3",
    "item_uq_q221_pascalReq_1",
    "item_uq_q222_pascalReq_2",
    "item_uq_q640_confidentialInfo",
    "item_uq_q720_memento_A",
    "item_uq_q720_memento_B",
    "item_uq_q720_memento_C",
    "item_uq_q720_memento_D",
    "item_uq_memberCard",
    "item_uq_resiBag",
    "item_uq_sachet_S",
    "item_uq_sachet_M",
    "item_uq_sachet_L",
    "item_uq_music_1",
    "item_uq_music_2",
    "item_uq_music_3",
    "item_uq_music_4",
    "item_uq_music_5",
    "item_uq_music_6",
    "item_uq_music_7",
    "item_uq_podSkin1",
    "item_uq_podSkin2",
    "item_uq_podSkin3",
    "item_uq_podSkin4",
    "item_uq_podSkin5",
    "item_uq_podSkin6",
    "item_uq_podSkin7",
    "item_uq_podSkin8",
    "item_uq_podSkin9",
    "item_uq_podSkin10",
    "item_uq_gunSkin1",
    "item_uq_gunSkin2",
    "item_uq_changeCloth",
    "item_uq_changeArmour1",
    "item_uq_changeArmour2",
    "item_uq_dlcCloth1",
    "item_uq_dlcCloth2",
    "item_uq_dlcCloth3",
    "item_uq_ribbon1",
    "item_uq_ribbon2",
    "item_uq_headdress_enemy",
    "item_uq_headdress_emile",
    "item_uq_emileMask",
    "item_uq_floralDecoration",
    "item_uq_adamGlasses",
    "item_uq_alienMask",
    "item_uq_noGoggles",
    "item_uq_wig",
    "item_uq_kingMask",
    "item_uq_valveHead1",
    "item_uq_valveHead2",
    "item_uq_valveHead3",
    "item_uq_valveHead4",
    "item_uq_ExSand",
    "item_uq_ExForest",
    "item_uq_matsudaMask",
    "item_uq_satoMask",
    "item_uq_hairSpray_A",
    "item_uq_hairSpray_B",
    "item_uq_hairSpray_C",
    "item_uq_hairSpray_D",
    "item_uq_hairSpray_E",
    "item_uq_hairSpray_F",
    "item_uq_hairSpray_G",
    "item_uq_hairSpray_H",
    "item_uq_hairSpray_I",
    "item_uq_hairSpray_J",
    "item_uq_hairSpray_K",
    "item_uq_hairSpray_L",
    "item_uq_hairSpray_M",
    "item_uq_hairSpray_N",
    "item_uq_hairSpray_O",
    "item_uq_hairSpray_P",
    "item_uq_hairSpray_Q",
    "item_uq_hairSpray_R",
    "item_uq_hairSpray_S",
    "skill_act_spear",
    "skill_act_illusion",
    "skill_act_hand",
    "skill_act_dance",
    "skill_act_execution",
    "skill_act_barrier",
    "skill_act_gluttony",
    "skill_act_lash",
    "skill_act_wire",
    "skill_act_fixedBattery",
    "skill_act_slowBomb",
    "skill_act_repair",
    "skill_act_smallBomb",
    "skill_act_gravityBomb",
    "skill_act_hold",
    "skill_act_ride",
    "skill_act_sonar",
    "skill_psv_atkUp_0",
    "skill_psv_atkUp_1",
    "skill_psv_atkUp_2",
    "skill_psv_atkUp_3",
    "skill_psv_atkUp_4",
    "skill_psv_atkUp_5",
    "skill_psv_atkUp_6",
    "skill_psv_atkUp_7",
    "skill_psv_atkUp_8",
    "skill_psv_downAtkUp_0",
    "skill_psv_downAtkUp_1",
    "skill_psv_downAtkUp_2",
    "skill_psv_downAtkUp_3",
    "skill_psv_downAtkUp_4",
    "skill_psv_downAtkUp_5",
    "skill_psv_downAtkUp_6",
    "skill_psv_downAtkUp_7",
    "skill_psv_downAtkUp_8",
    "skill_psv_criticalUp_0",
    "skill_psv_criticalUp_1",
    "skill_psv_criticalUp_2",
    "skill_psv_criticalUp_3",
    "skill_psv_criticalUp_4",
    "skill_psv_criticalUp_5",
    "skill_psv_criticalUp_6",
    "skill_psv_criticalUp_7",
    "skill_psv_criticalUp_8",
    "skill_psv_podAtkUp_0",
    "skill_psv_podAtkUp_1",
    "skill_psv_podAtkUp_2",
    "skill_psv_podAtkUp_3",
    "skill_psv_podAtkUp_4",
    "skill_psv_podAtkUp_5",
    "skill_psv_podAtkUp_6",
    "skill_psv_podAtkUp_7",
    "skill_psv_podAtkUp_8",
    "skill_psv_coolTimeDown_0",
    "skill_psv_coolTimeDown_1",
    "skill_psv_coolTimeDown_2",
    "skill_psv_coolTimeDown_3",
    "skill_psv_coolTimeDown_4",
    "skill_psv_coolTimeDown_5",
    "skill_psv_coolTimeDown_6",
    "skill_psv_coolTimeDown_7",
    "skill_psv_coolTimeDown_8",
    "skill_psv_stDefUp_0",
    "skill_psv_stDefUp_1",
    "skill_psv_stDefUp_2",
    "skill_psv_stDefUp_3",
    "skill_psv_stDefUp_4",
    "skill_psv_stDefUp_5",
    "skill_psv_stDefUp_6",
    "skill_psv_stDefUp_7",
    "skill_psv_stDefUp_8",
    "skill_psv_enDefUp_0",
    "skill_psv_enDefUp_1",
    "skill_psv_enDefUp_2",
    "skill_psv_enDefUp_3",
    "skill_psv_enDefUp_4",
    "skill_psv_enDefUp_5",
    "skill_psv_enDefUp_6",
    "skill_psv_enDefUp_7",
    "skill_psv_enDefUp_8",
    "skill_psv_damageInv_0",
    "skill_psv_damageInv_1",
    "skill_psv_damageInv_2",
    "skill_psv_damageInv_3",
    "skill_psv_damageInv_4",
    "skill_psv_damageInv_5",
    "skill_psv_damageInv_6",
    "skill_psv_damageInv_7",
    "skill_psv_damageInv_8",
    "skill_psv_hpUp_0",
    "skill_psv_hpUp_1",
    "skill_psv_hpUp_2",
    "skill_psv_hpUp_3",
    "skill_psv_hpUp_4",
    "skill_psv_hpUp_5",
    "skill_psv_hpUp_6",
    "skill_psv_hpUp_7",
    "skill_psv_hpUp_8",
    "skill_psv_atkDrain_0",
    "skill_psv_atkDrain_1",
    "skill_psv_atkDrain_2",
    "skill_psv_atkDrain_3",
    "skill_psv_atkDrain_4",
    "skill_psv_atkDrain_5",
    "skill_psv_atkDrain_6",
    "skill_psv_atkDrain_7",
    "skill_psv_atkDrain_8",
    "skill_psv_defeatDrain_0",
    "skill_psv_defeatDrain_1",
    "skill_psv_defeatDrain_2",
    "skill_psv_defeatDrain_3",
    "skill_psv_defeatDrain_4",
    "skill_psv_defeatDrain_5",
    "skill_psv_defeatDrain_6",
    "skill_psv_defeatDrain_7",
    "skill_psv_defeatDrain_8",
    "skill_psv_autoRec_0",
    "skill_psv_autoRec_1",
    "skill_psv_autoRec_2",
    "skill_psv_autoRec_3",
    "skill_psv_autoRec_4",
    "skill_psv_autoRec_5",
    "skill_psv_autoRec_6",
    "skill_psv_autoRec_7",
    "skill_psv_autoRec_8",
    "skill_psv_avoidLenUp_0",
    "skill_psv_avoidLenUp_1",
    "skill_psv_avoidLenUp_2",
    "skill_psv_avoidLenUp_3",
    "skill_psv_avoidLenUp_4",
    "skill_psv_avoidLenUp_5",
    "skill_psv_avoidLenUp_6",
    "skill_psv_avoidLenUp_7",
    "skill_psv_avoidLenUp_8",
    "skill_psv_moveSpdUp_0",
    "skill_psv_moveSpdUp_1",
    "skill_psv_moveSpdUp_2",
    "skill_psv_moveSpdUp_3",
    "skill_psv_moveSpdUp_4",
    "skill_psv_moveSpdUp_5",
    "skill_psv_moveSpdUp_6",
    "skill_psv_moveSpdUp_7",
    "skill_psv_moveSpdUp_8",
    "skill_psv_itemDropUp_0",
    "skill_psv_itemDropUp_1",
    "skill_psv_itemDropUp_2",
    "skill_psv_itemDropUp_3",
    "skill_psv_itemDropUp_4",
    "skill_psv_itemDropUp_5",
    "skill_psv_itemDropUp_6",
    "skill_psv_itemDropUp_7",
    "skill_psv_itemDropUp_8",
    "skill_psv_expUp_0",
    "skill_psv_expUp_1",
    "skill_psv_expUp_2",
    "skill_psv_expUp_3",
    "skill_psv_expUp_4",
    "skill_psv_expUp_5",
    "skill_psv_expUp_6",
    "skill_psv_expUp_7",
    "skill_psv_expUp_8",
    "skill_psv_atkEffect_0",
    "skill_psv_atkEffect_1",
    "skill_psv_atkEffect_2",
    "skill_psv_atkEffect_3",
    "skill_psv_atkEffect_4",
    "skill_psv_atkEffect_5",
    "skill_psv_atkEffect_6",
    "skill_psv_atkEffect_7",
    "skill_psv_atkEffect_8",
    "skill_psv_berserk_0",
    "skill_psv_berserk_1",
    "skill_psv_berserk_2",
    "skill_psv_berserk_3",
    "skill_psv_berserk_4",
    "skill_psv_berserk_5",
    "skill_psv_berserk_6",
    "skill_psv_berserk_7",
    "skill_psv_berserk_8",
    "skill_psv_damageDrain_0",
    "skill_psv_damageDrain_1",
    "skill_psv_damageDrain_2",
    "skill_psv_damageDrain_3",
    "skill_psv_damageDrain_4",
    "skill_psv_damageDrain_5",
    "skill_psv_damageDrain_6",
    "skill_psv_damageDrain_7",
    "skill_psv_damageDrain_8",
    "skill_psv_autoReflect_0",
    "skill_psv_autoReflect_1",
    "skill_psv_autoReflect_2",
    "skill_psv_autoReflect_3",
    "skill_psv_autoReflect_4",
    "skill_psv_autoReflect_5",
    "skill_psv_autoReflect_6",
    "skill_psv_autoReflect_7",
    "skill_psv_autoReflect_8",
    "skill_psv_guts_0",
    "skill_psv_guts_1",
    "skill_psv_guts_2",
    "skill_psv_guts_3",
    "skill_psv_guts_4",
    "skill_psv_guts_5",
    "skill_psv_guts_6",
    "skill_psv_guts_7",
    "skill_psv_guts_8",
    "skill_psv_witchTime_0",
    "skill_psv_witchTime_1",
    "skill_psv_witchTime_2",
    "skill_psv_witchTime_3",
    "skill_psv_witchTime_4",
    "skill_psv_witchTime_5",
    "skill_psv_witchTime_6",
    "skill_psv_witchTime_7",
    "skill_psv_witchTime_8",
    "skill_psv_superArmour_0",
    "skill_psv_superArmour_1",
    "skill_psv_superArmour_2",
    "skill_psv_superArmour_3",
    "skill_psv_superArmour_4",
    "skill_psv_superArmour_5",
    "skill_psv_superArmour_6",
    "skill_psv_superArmour_7",
    "skill_psv_superArmour_8",
    "skill_psv_HUD_itemScan",
    "skill_psv_counterAction_0",
    "skill_psv_counterAction_1",
    "skill_psv_counterAction_2",
    "skill_psv_counterAction_3",
    "skill_psv_counterAction_4",
    "skill_psv_counterAction_5",
    "skill_psv_counterAction_6",
    "skill_psv_counterAction_7",
    "skill_psv_counterAction_8",
    "skill_psv_holdAction_0",
    "skill_psv_holdAction_1",
    "skill_psv_holdAction_2",
    "skill_psv_holdAction_3",
    "skill_psv_holdAction_4",
    "skill_psv_holdAction_5",
    "skill_psv_holdAction_6",
    "skill_psv_holdAction_7",
    "skill_psv_holdAction_8",
    "skill_psv_chargeAtk_0",
    "skill_psv_chargeAtk_1",
    "skill_psv_chargeAtk_2",
    "skill_psv_chargeAtk_3",
    "skill_psv_chargeAtk_4",
    "skill_psv_chargeAtk_5",
    "skill_psv_chargeAtk_6",
    "skill_psv_chargeAtk_7",
    "skill_psv_chargeAtk_8",
    "skill_psv_autoItem_0",
    "skill_psv_autoItem_1",
    "skill_psv_autoItem_2",
    "skill_psv_autoItem_3",
    "skill_psv_autoItem_4",
    "skill_psv_autoItem_5",
    "skill_psv_autoItem_6",
    "skill_psv_autoItem_7",
    "skill_psv_autoItem_8",
    "skill_psv_ctrlTimeUp_0",
    "skill_psv_ctrlTimeUp_1",
    "skill_psv_ctrlTimeUp_2",
    "skill_psv_ctrlTimeUp_3",
    "skill_psv_ctrlTimeUp_4",
    "skill_psv_ctrlTimeUp_5",
    "skill_psv_ctrlTimeUp_6",
    "skill_psv_ctrlTimeUp_7",
    "skill_psv_ctrlTimeUp_8",
    "skill_psv_stan_0",
    "skill_psv_stan_1",
    "skill_psv_stan_2",
    "skill_psv_stan_3",
    "skill_psv_stan_4",
    "skill_psv_stan_5",
    "skill_psv_stan_6",
    "skill_psv_stan_7",
    "skill_psv_stan_8",
    "skill_psv_burst_0",
    "skill_psv_burst_1",
    "skill_psv_burst_2",
    "skill_psv_burst_3",
    "skill_psv_burst_4",
    "skill_psv_burst_5",
    "skill_psv_burst_6",
    "skill_psv_burst_7",
    "skill_psv_burst_8",
    "skill_psv_dropRecUp_0",
    "skill_psv_dropRecUp_1",
    "skill_psv_dropRecUp_2",
    "skill_psv_dropRecUp_3",
    "skill_psv_dropRecUp_4",
    "skill_psv_dropRecUp_5",
    "skill_psv_dropRecUp_6",
    "skill_psv_dropRecUp_7",
    "skill_psv_dropRecUp_8",
    "skill_psv_deathAgony",
    "skill_psv_baseHUD",
    "skill_psv_soundIndicator",
    "skill_psv_enemyInfo",
    "skill_psv_OS",
    "skill_psv_bulletSlow",
    "skill_psv_comboContinue",
    "skill_psv_bombExplosion",
    "skill_psv_itemAdsorption",
    "skill_psv_HUD_skillGauge",
    "skill_psv_HUD_log",
    "skill_psv_HUD_miniMap",
    "skill_psv_HUD_expGauge",
    "skill_psv_HUD_saveIcon",
    "skill_psv_HUD_damage",
    "skill_psv_HUD_destination",
    "skill_psv_HUD_automatic",
    "skill_psv_HUD_fishZone",
    "skill_psv_auto_atk",
    "skill_psv_auto_shoot",
    "skill_psv_auto_avoid",
    "skill_psv_auto_pod",
    "skill_psv_auto_weapon",
    "capacity_1",
    "capacity_2",
    "capacity_3",
    "capacity_4",
    "capacity_6",
    "capacity_7",
    "capacity_8",
    "achievement_20",
    "achievement_21",
    "achievement_23",
    "achievement_24",
    "achievement_25",
    "achievement_26",
    "achievement_27",
    "achievement_28",
    "achievement_29",
    "achievement_30",
    "achievement_32",
    "achievement_33",
    "achievement_34",
    "achievement_35",
    "achievement_36",
    "achievement_37",
    "achievement_38",
    "achievement_39",
    "achievement_40",
    "achievement_41",
    "achievement_42",
    "achievement_43",
    "achievement_44",
    "achievement_45",
    "achievement_46",
    "achievement_47",
    "composition_pod1",
    "composition_pod2",
    "composition_pod3",
    "picEvent_1",
    "picEvent_2",
    "picEvent_3",
    "picEvent_4",
    "picEvent_5",
    "picEvent_6",
    "picEvent_7",
    "picEvent_8",
    "picEvent_11",
    "picEvent_12",
    "picEvent_13",
    "fish_1",
    "fish_2",
    "fish_3",
    "fish_4",
    "fish_5",
    "fish_6",
    "fish_7",
    "fish_8",
    "fish_9",
    "fish_10",
    "fish_11",
    "fish_12",
    "fish_13",
    "fish_14",
    "fish_15",
    "fish_16",
    "fish_17",
    "fish_18",
    "fish_19",
    "fish_20",
    "fish_21",
    "fish_22",
    "fish_23",
    "fish_24",
    "fish_25",
    "fish_26",
    "fish_27",
    "fish_28",
    "fish_29",
    "fish_30",
    "fish_31",
    "fish_32",
    "fish_33",
    "fish_34",
    "fish_35",
    "fish_36",
    "fish_37",
    "fish_38",
    "fish_39",
    "fish_40",
    "fish_41",
    "file_pearlHarbor_1",
    "file_pearlHarbor_2",
    "file_pearlHarbor_3",
    "file_pearlHarbor_4",
    "file_pearlHarbor_5",
    "file_pearlHarbor_6",
    "file_pearlHarbor_7",
    "file_memory_1",
    "file_memory_2",
    "file_memory_3",
    "file_h_letter",
    "file_h_11BDesertion",
    "file_h_bombRecipe",
    "file_robo_1",
    "file_robo_2",
    "file_robo_3",
    "file_robo_4",
    "file_robo_6",
    "file_robo_7",
    "file_robo_8",
    "file_h_flyer_kj",
    "file_eng_1",
    "file_eng_2",
    "file_eng_3",
    "file_h_childMemory",
    "file_server_1",
    "file_server_2",
    "file_server_3",
    "file_h_testament",
    "file_h_animalRoboMemory",
    "file_h_robo_5",
    "file_lostInfo_factory_1",
    "file_lostInfo_factory_2",
    "file_lostInfo_submerge_1",
    "file_lostInfo_park_1",
    "file_lostInfo_park_2",
    "file_lostInfo_castle_1",
    "file_lostInfo_woods_1",
    "file_lostInfo_desert_1",
    "file_lostInfo_ruins_1",
    "file_lostInfo_ruins_2",
    "file_lostInfo_ruins_3",
    "file_lostInfo_ruins_4",
    "file_mysteryStone1",
    "file_mysteryStone2",
    "file_mysteryStone3",
    "file_mysteryStone4",
    "file_report_1",
    "file_report_2",
    "file_report_3",
    "file_report_4",
    "file_report_5",
    "file_report_6",
    "file_report_7",
    "file_report_8",
    "file_report_9",
    "file_report_10",
    "file_report_11",
    "file_h_roboReport"
};

/*BOOL __stdcall new_WriteConsoleW( HANDLE hConsoleOutput , const PVOID lpBuffer , DWORD nNumberOfCharsToWrite , LPDWORD lpNumberOfCharsWritten , LPVOID lpReserved )
{
    bool bRet = ( ( bool( __stdcall* )( HANDLE , const PVOID , DWORD , LPDWORD , LPVOID ) )D_WriteConsoleW->pOld )( hConsoleOutput , lpBuffer , nNumberOfCharsToWrite , lpNumberOfCharsWritten , lpReserved );
    if ( hConsoleOutput != GetStdHandle( STD_OUTPUT_HANDLE ) )
        CONSOLEColorDEBUG(FOREGROUND_ROSE, TEXT( "%s\n" ) , lpBuffer );

    return bRet;
}

void __stdcall new_OutputDebugStringW( LPCWSTR lpOutputString )
{
    ( ( void( __stdcall* )( LPCWSTR ) )D_OutputDebugStringW->pOld )( lpOutputString );
    CONSOLEColorDEBUG(FOREGROUND_ROSE, TEXT( "%s\n" ) , lpOutputString );
}

SHORT __stdcall new_GetKeyState( int vKey )
{
    SHORT sRet = ( ( SHORT( __stdcall* )( int ) )D_GetKeyState->pOld )( vKey );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "Pressed vKey: 0x%p\n" ) , vKey );

    return sRet;
}

BOOL __stdcall new_GetPrivateProfileStructA( LPCSTR lpszSection , LPCSTR lpszKey , LPVOID lpStruct , UINT uSizeStruct , LPCSTR szFile )
{
    BOOL bRet = ( ( BOOL( __stdcall* )( LPCSTR , LPCSTR , LPVOID , UINT , LPCSTR ) )D_GetPrivateProfileStructA->pOld )( lpszSection , lpszKey , lpStruct , uSizeStruct , szFile );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "new_GetPrivateProfileStructA: %s %s 0x%p %i %s" ) , stdString( AutoConvertS( lpszSection ) ).c_str()
                                     , stdString( AutoConvertS( lpszKey ) ).c_str()
                                     , lpStruct
                                     , uSizeStruct
                                     , stdString( AutoConvertS( szFile ) ).c_str() );

    return bRet;
}

BOOL __stdcall new_WritePrivateProfileStructA( LPCSTR lpszSection , LPCSTR lpszKey , LPVOID lpStruct , UINT uSizeStruct , LPCSTR szFile )
{
    BOOL bRet = ( ( BOOL( __stdcall* )( LPCSTR , LPCSTR , LPVOID , UINT , LPCSTR ) )D_WritePrivateProfileStructA->pOld )( lpszSection , lpszKey , lpStruct , uSizeStruct , szFile );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "new_WritePrivateProfileStructA: %s %s 0x%p %i %s" ) , stdString( AutoConvertS( lpszSection ) ).c_str()
                                     , stdString( AutoConvertS( lpszKey ) ).c_str()
                                     , lpStruct
                                     , uSizeStruct
                                     , stdString( AutoConvertS( szFile ) ).c_str() );

    return bRet;
}

BOOL __stdcall new_ReadFile( HANDLE hFile , LPVOID lpBuffer , DWORD nNumberOfBytesToRead , LPDWORD lpNumberOfBytesRead , LPOVERLAPPED lpOverlapped )
{
    BOOL pRet = ( ( BOOL( __stdcall * )( HANDLE , LPVOID , DWORD , LPDWORD , LPOVERLAPPED ) )D_ReadFile->pOld )( hFile , lpBuffer , nNumberOfBytesToRead , lpNumberOfBytesRead , lpOverlapped );
    return pRet;
}

int new_wsprintfW( LPWSTR Str1 , LPCWSTR Str2 , ... )
{
    va_list list;
    va_start( list , Str2 );
    int iRet = ( ( int( __stdcall* )( LPWSTR , LPCWSTR , ... ) )D_wsprintfW->pOld )( Str1 , Str2 , list );
    va_end( list );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "%s\n" ) , Str1 );

    return iRet;
}
 */

 // Search by string the item id.
signed __int64 sub_1405DE6E0( __int64 a1 , char *a2 )
{
    __int64 cRet = ( ( __int64( *) ( __int64 , char* ) ) D_Unknown->pOld )( a1 , a2 );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "sub_1405DE6E0 ( %s %i %i ) \n" ) , a2 , a1 , cRet );

    return cRet;
}

// Add item.
int sub_1405DC410( __int64 a1 , __int64 a2 , __int64 a3 , __int64 a4 )
{
    int cRet = ( ( int( *)  ( __int64 , __int64 , __int64 , __int64 ) ) D_Unknown2->pOld )( a1 , a2 , a3 , a4 );

    N_Console::Print<FOREGROUND_ROSE>( TEXT( "sub_1405DC410 ( Input: %i - ItemID: %i - Amount: %i - ?: %i - Ret: %i RetAddress: 0x%p) \n" ) , a1 , a2 , a3 , a4 , cRet , _ReturnAddress() );

    return cRet;
}

// Printing stuffs?

__int64 sub_140967D50( char *a1 , unsigned __int64 a2 )
{
    __int64 cRet = ( ( __int64( *) ( char *a1 , unsigned __int64 ) ) D_Unknown3->pOld )( a1 , a2 );

    if ( ( HEX ) _ReturnAddress() == 0x00000001405DE3F4 )
        N_Console::Print<FOREGROUND_ROSE>( TEXT( "\"%s\",\n" ) , a1 );

    return cRet;
}

signed __int64 sub_1405EE630( __int64 a1 )
{
    __int64 cRet = ( ( __int64( *) ( __int64 ) ) D_Unknown4->pOld )( a1 );

    return cRet;
}

signed __int64 sub_1405EE8D0( __int64 a1 , int a2 , int a3 )
{
    __int64 cRet = ( ( __int64( *) ( __int64 , int , int ) ) D_Unknown5->pOld )( a1 , a2 , a3 );

    N_Console::Print<FOREGROUND_YELLOW>( TEXT( "sub_1405EE8D0 %i %i %i\n" ) , a1 , a2 , a3 );

    return cRet;
}

Pointer _RoutineHack( S_Routine *SRoutine )
{
    N_Process::Process *pCurrentProcess = new N_Process::Process( GetCurrentProcessId() );

    N_Console::Open();

   // N_Hook::Init();

   /* D_GetKeyState = new N_Hook::DetourFunction( ( Pointer ) new_GetKeyState , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "user32.dll" ) ) , "GetKeyState" )
                                              , TEXT( "GetKeyState" ) );

    D_GetPrivateProfileStructA = new N_Hook::DetourFunction( ( Pointer ) new_GetPrivateProfileStructA , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll" ) ) , "GetPrivateProfileStructA" )
                                                           , TEXT( "GetPrivateProfileStructA" ) );

    D_WritePrivateProfileStructA = new N_Hook::DetourFunction( ( Pointer ) new_WritePrivateProfileStructA , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll" ) ) , "WritePrivateProfileStructA" )
                                                             , TEXT( "WritePrivateProfileStructA" ) );

    D_ReadFile = new N_Hook::DetourFunction( ( Pointer ) new_ReadFile , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll" ) ) , "ReadFile" )
                                           , TEXT( "ReadFile" ) );

    D_wsprintfW = new N_Hook::DetourFunction( ( Pointer ) new_wsprintfW , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "user32.dll" ) ) , "wsprintfW" )
                                            , TEXT( "wsprintfW" ) );

    D_WriteConsoleW = new N_Hook::DetourFunction( ( Pointer ) new_WriteConsoleW , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll" ) ) , "WriteConsoleW" )
                                                , TEXT( "WriteConsoleW" ) );

    D_OutputDebugStringW = new N_Hook::DetourFunction( ( Pointer ) new_OutputDebugStringW , ( Pointer ) GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll" ) ) , "OutputDebugStringW" )
                                                     , TEXT( "OutputDebugStringW" ) );        */

  // D_Unknown = new N_Hook::DetourFunction( ( Pointer ) sub_1405DE6E0 , ( Pointer ) 0x1405DE6E0 , TEXT( "Unknown" ) );
  // D_Unknown2 = new N_Hook::DetourFunction( ( Pointer ) sub_1405DC410 , ( Pointer ) 0x1405DC410 , TEXT( "Unknown2" ) );
  //  D_Unknown3 = new N_Hook::DetourFunction( ( Pointer ) sub_140967D50 , ( Pointer ) 0x140967D50 , TEXT( "Unknown3" ) );
 // D_Unknown4 = new N_Hook::DetourFunction( ( Pointer ) sub_1405EE630 , ( Pointer ) 0x1405EE630 , TEXT( "Unknown4" ) );
 // D_Unknown5 = new N_Hook::DetourFunction( ( Pointer ) sub_1405EE8D0 , ( Pointer ) 0x1405EE8D0 , TEXT( "Unknown5" ) );

   // N_Hook::ApplyHooks();

    /*SigScanning SigScanNoCoolDownPods( pCurrentProcess->pProcess , TEXT( "Pods no cooldown" ) );
    SigScanNoCoolDownPods.Scan( { 0xF3, 0x0F, 0x11, 0x84, 0xC3, 0x24, 0x6A, 0x01, 0x00, 0xF3, 0x0F, 0x11, 0x84, 0xC3, 0x20, 0x6A,
                                0x01, 0x00, 0x83, 0xFE, 0x01, 0x7C, 0x23, 0x8B, 0x83, 0x20, 0x08, 0x01, 0x00 } , TEXT( "NieRAutomata.exe" ) );

    SigScanNoCoolDownPods.PrintAllOffsets();   */

    SigScanningFile SigScanAirDash( pCurrentProcess->pProcess , TEXT( "Air dash unlimited." ) );
    SigScanAirDash.Scan( std::vector<Byte>{ 0xC7 , 0x83 , 0x88 , 0x0A , 0x01 , 0x00 , 0x01 , 0x00 , 0x00 , 0x00 } , TEXT( "NieRAutomata.exe" ) );
    SigScanAirDash.PrintAllOffsets();

    SigScanningFile SigScanInfJumps( pCurrentProcess->pProcess , TEXT( "Jumps unlimited." ) );
    SigScanInfJumps.Scan( std::vector<Byte>{ 0x83 , 0xBB , 0xA8 , 0x14 , 0x00 , 0x00 , 0x02 , 0x0F } , TEXT( "NieRAutomata.exe" ) );
    SigScanInfJumps.PrintAllOffsets();

    SigScanningFile SigScanGodHacking( pCurrentProcess->pProcess , TEXT( "Hack god mode enabled" ) );
    SigScanGodHacking.Scan( std::vector<Byte>{ 0xFF , 0x89 , 0xDC , 0x28 , 0x01 , 0x00 , 0x48 , 0x8B , 0x01 , 0x48 , 0x8D , 0x15 , 0xFE , 0xCF , 0xC4 , 0x00 } , TEXT( "NieRAutomata.exe" ) );
    SigScanGodHacking.PrintAllOffsets();

    /*SigScanning SigScanInfJumps( pCurrentProcess->pProcess , TEXT( "Jumps unlimited." ) );
    SigScanInfJumps.Scan( { 0x83,0xB9,0xA8,0x14,0x00,0x00,0x02,0x7C,0x0A,0x33,0xF6,0x89,0xB1,0xB8,0x0A,0x01 } , TEXT( "NieRAutomata.exe" ) );
    SigScanInfJumps.PrintAllOffsets();*/

    while ( 1 )
    {
        if ( GetAsyncKeyState( VK_F1 ) )
        {
            for ( int i = 0; i < 728; i++ )
            {
                __int64 cRet = ( ( __int64( *) ( __int64 , char* ) ) ( Pointer ) 0x1405DE6E0 )( 0 , ItemTables[ i ] );
                int Added = ( ( int( *)  ( __int64 , __int64 , __int64 , __int64 ) )( Pointer ) 0x1405DC410 )( cRet , cRet , 1 , 1 );
                N_Console::Print<FOREGROUND_CYAN>( TEXT( "Item: %s - ID: %i - " ) , ItemTables[ i ] , cRet );
                N_Console::Print<FOREGROUND_CYAN>( TEXT( "Added: %i\n" ) , Added );
            }
        }

        if ( GetAsyncKeyState( VK_F2 ) )
        {
            stdString i1 = N_Console::Input( TEXT( "Change money to? \n" ) );
            uHEX32 ii1 = ( uHEX32 ) _wtoi( i1.c_str() );

            *( puHEX32 ) ( 0x14197C4C0 ) = ii1;
        }

        if ( GetAsyncKeyState( VK_F3 ) )
        {
            stdString i1 = N_Console::Input( TEXT( "Change exp to? \n" ) );
            uHEX32 ii1 = ( uHEX32 ) _wtoi( i1.c_str() );

            *( puHEX32 ) ( 0x141984670 ) = ii1;
        }

        if ( GetAsyncKeyState( VK_F4 ) )
        {
            stdString i1 = N_Console::Input( TEXT( "Change max chip size to? \n" ) );
            uHEX32 ii1 = ( uHEX32 ) _wtoi( i1.c_str() );
            *( puHEX32 ) ( 0x141105BC4 ) = ii1;
        }

        if ( GetAsyncKeyState( VK_F5 ) )
        {
            stdString Amount = N_Console::Input( TEXT( "Lvl for weapons/pods?\n" ) );

            int iAmount = _wtoi( Amount.c_str() );

            for ( HEX i = 0x14197D0C4; i <= 0x14197DFC0; i += 0x14 )
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Changed weapon lvl: %i 0x%p\n" ) , iAmount , i );
                *( int * ) ( i ) = iAmount;
            }

            ( ( __int64( *) ( __int64 , int , int ) ) ( Pointer ) 0x1405EE8D0 )( 6001 , iAmount - 1 , 0 );
            ( ( __int64( *) ( __int64 , int , int ) )( Pointer ) 0x1405EE8D0 )( 6002 , iAmount - 1 , 1 );
            ( ( __int64( *) ( __int64 , int , int ) ) ( Pointer ) 0x1405EE8D0 )( 6003 , iAmount - 1 , 2 );
        }

        /*static bool bRevert = false;

        if ( GetAsyncKeyState( VK_F12 ) )
        {
            for ( auto it = SigScanRemoveChecksPodsWeaps.OffsetsFound.begin(); it != SigScanRemoveChecksPodsWeaps.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->second.size(); ic++ )
                {
                    Bytes b = ( Bytes ) it->second[ ic ];

                    HEX HexOldProtect = 0;
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , 3 , PAGE_EXECUTE_READWRITE , &HexOldProtect );

                    if ( bRevert )
                    {
                        b[ 0 ] = 0x41;
                        b[ 1 ] = 0x3B;
                        b[ 2 ] = 0xC2;
                        N_Console::Print<FOREGROUND_CYAN>( TEXT( "Removed bypass materials checks for weapons and pods! 0x%02X 0x%02X 0x%02X\n" ) , b[ 0 ] , b[ 1 ] , b[ 2 ] );
                    }
                    else
                    {
                        b[ 0 ] = 0x90;
                        b[ 1 ] = 0x90;
                        b[ 2 ] = 0x90;
                        N_Console::Print<FOREGROUND_CYAN>( TEXT( "Bypassed materials checks for weapons and pods! 0x%02X 0x%02X 0x%02X\n" ) , b[ 0 ] , b[ 1 ] , b[ 2 ] );
                    }

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , 3 , HexOldProtect );
                }
            }

            bRevert = !bRevert;
        } */

        static bool bRevertF6 = true;
        if ( GetAsyncKeyState( VK_F6 ) )
        {
           /* std::vector<Byte> OpCodes;

            if ( bRevertF6 )
                OpCodes = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            else
                OpCodes = { 0xF3, 0x0F, 0x11, 0x84, 0xC3, 0x24, 0x6A, 0x01, 0x00 };

            for ( auto it = SigScanNoCoolDownPods.OffsetsFound.begin(); it != SigScanNoCoolDownPods.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->second.size(); ic++ )
                {
                    HEX HexOldProtect = 0;
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , PAGE_EXECUTE_READWRITE , &HexOldProtect );

                    for ( int i = 0; i < OpCodes.size(); i++ )
                    {
                        ( ( Bytes ) it->second[ ic ] )[ i ] = OpCodes[ i ];
                    }

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , HexOldProtect );
                }
            } */

            if ( bRevertF6 )
            {
                uHEX32 HexOldProtect = 0;
                N_VirtualMemory::VirtualModifyProtectionFlags( ( Pointer ) 0x14014838A , pCurrentProcess->pProcess , sizeof( DWORD ) , PAGE_EXECUTE_READWRITE , &HexOldProtect );
                *( DWORD* ) ( 0x14014838A ) = 0;
                N_VirtualMemory::VirtualModifyProtectionFlags( ( Pointer ) 0x14014838A , pCurrentProcess->pProcess , sizeof( DWORD ) , HexOldProtect );

                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Cool down disabled for pods & ship.\n" ) );
            }
            else
            {
                uHEX32 HexOldProtect = 0;
                N_VirtualMemory::VirtualModifyProtectionFlags( ( Pointer ) 0x14014838A , pCurrentProcess->pProcess , sizeof( DWORD ) , PAGE_EXECUTE_READWRITE , &HexOldProtect );
                *( DWORD* ) ( 0x14014838A ) = 1;
                N_VirtualMemory::VirtualModifyProtectionFlags( ( Pointer ) 0x14014838A , pCurrentProcess->pProcess , sizeof( DWORD ) , HexOldProtect );

                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Cool down enabled for pods & ship.\n" ) );
            }

            bRevertF6 = !bRevertF6;
        }

        static bool bRevertF7 = true;
        if ( GetAsyncKeyState( VK_F7 ) )
        {
            std::vector<Byte> OpCodes = { 0xFF , 0x0F , 0x8C };

            if ( !bRevertF7 )
            {
                OpCodes = { 0x02 , 0x0F , 0x8D };
            }

            for ( auto it = SigScanInfJumps.OffsetsFound.begin(); it != SigScanInfJumps.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->pOffsets.size(); ic++ )
                {
                    uHEX32 HexOldProtect = 0;
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , PAGE_EXECUTE_READWRITE , &HexOldProtect );

                    for ( int i = 0; i < OpCodes.size(); i++ )
                    {
                        ( ( Bytes ) ( ( HEX ) it->pOffsets[ ic ] + 0x6 ) )[ i ] = OpCodes[ i ];
                    }

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , HexOldProtect );
                }
            }

            if ( bRevertF7 )
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "InfiniteJumps enabled.\n" ) );
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "InfiniteJumps disabled. \n" ) );
            }

            bRevertF7 = !bRevertF7;
        }
          /*
        static bool bRevertF6 = true;
        if ( GetAsyncKeyState( VK_F6 ) )
        {
            std::vector<Byte> vBInfJumps { 0x83, 0xB9, 0xA8, 0x14, 0x00, 0x00, 0x01, 0x0F, 0x8E, 0x3E, 0xFC, 0x1E, 0x00, 0xC7, 0x81, 0xA8, 0x14, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x2F, 0xFC, 0x1E, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            std::vector<Byte> vJmp { 0xE9 ,0xB7 ,0x03 ,0xE1 ,0xFF ,0x90 ,0x90 };

            if ( !bRevertF6 )
            {
                vJmp = { 0x83,  0xB9 ,  0xA8 , 0x14 , 0x00 , 0x00 , 0x02 };
            }

            HEX HexOldP = 0;

            Pointer pAddress = N_VirtualMemory::VirtualAllocation( vBInfJumps.size() , N_VirtualMemory::MapFillProtectFlags( vBInfJumps.size() , PAGE_EXECUTE_READWRITE )
                                                                 , pCurrentProcess->pProcess , ( Pointer ) 0x13FFF0000 );

            if ( pAddress == nullptr || pAddress != (Pointer)0x13FFF0000 )
            {
                CONSOLEDEBUG( TEXT( "Failed Alloc: 0x%X \n" ) , GetLastError() );
                continue;
            }

            bool b = N_VirtualMemory::VirtualModifyProtectionFlags( pAddress , pCurrentProcess->pProcess , vBInfJumps.size() , PAGE_EXECUTE_READWRITE , &HexOldP );

            if ( !b )
            {
                CONSOLEDEBUG( TEXT( "Failed Protection: 0x%X \n" ) , GetLastError() );
                continue;
            }

            CONSOLEColorDEBUG(FOREGROUND_CYAN, TEXT( "InfJumps: %p %i \n" ) , pAddress , b );

            for ( int i = 0; i < vBInfJumps.size(); i++ )
            {
                ( ( Bytes ) pAddress )[ i ] = vBInfJumps[ i ];
            }

            for ( auto it = SigScanInfJumps.OffsetsFound.begin(); it != SigScanInfJumps.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->second.size(); ic++ )
                {
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , vJmp.size() , PAGE_EXECUTE_READWRITE , &HexOldP );

                    for ( int i = 0; i < vJmp.size(); i++ )
                        ( ( Bytes ) it->second[ ic ] )[ i ] = vJmp[ i ];

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->second[ ic ] , pCurrentProcess->pProcess , vJmp.size() , HexOldP );
                }
            }

            if ( bRevertF6 )
            {
                CONSOLEColorDEBUG(FOREGROUND_CYAN, TEXT( "InfiniteJumps enabled.\n" ) );
            }
            else
            {
                CONSOLEColorDEBUG(FOREGROUND_CYAN, TEXT( "InfiniteJumps disabled. \n" ) );
            }

            bRevertF6 = !bRevertF6;
        }       */

       /* if ( GetAsyncKeyState( VK_F6 ) )
        {
            stdString ID = N_Console::Input( TEXT( "Item ID?\n" ) );
            stdString Amount = N_Console::Input( TEXT( "Amount?\n" ) );

            __int64 iID = _atoi64( ID.c_str() );
            __int64 iAmount = _atoi64( ID.c_str() );

            N_Console::Print<FOREGROUND_CYAN>( TEXT( "Added item: %i -> %i\n" ) , iID ,
                ( ( int( *) ( __int64 , __int64 , __int64 , __int64 ) ) D_Unknown2->pOld )( iID , iAmount , 1 , 1 ) );
        }  */

        static bool bRevertF8 = true;
        if ( GetAsyncKeyState( VK_F8 ) )
        {
            std::vector<Byte> OpCodes;

            if ( bRevertF8 )
                OpCodes = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            else
                OpCodes = { 0xFF , 0x89 , 0xDC , 0x28 , 0x01 , 0x00 };

            for ( auto it = SigScanGodHacking.OffsetsFound.begin(); it != SigScanGodHacking.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->pOffsets.size(); ic++ )
                {
                    uHEX32 HexOldProtect = 0;
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , PAGE_EXECUTE_READWRITE , &HexOldProtect );

                    for ( int i = 0; i < OpCodes.size(); i++ )
                    {
                        ( ( Bytes ) it->pOffsets[ ic ] )[ i ] = OpCodes[ i ];
                    }

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , HexOldProtect );
                }
            }

            if ( bRevertF8 )
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "God mode enabled for hacking.\n" ) );
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "God mode disabled for hacking.\n" ) );
            }

            bRevertF8 = !bRevertF8;
        }

        static bool bRevertF9 = true;
        if ( GetAsyncKeyState( VK_F9 ) )
        {
            std::vector<Byte> OpCodes;

            if ( bRevertF9 )
                OpCodes = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            else
                OpCodes = { 0xC7 , 0x83 ,0x88 ,0x0A ,0x01 ,0x00 ,0x01 ,0x00, 0x00 ,0x00 };

            for ( auto it = SigScanAirDash.OffsetsFound.begin(); it != SigScanAirDash.OffsetsFound.end(); it++ )
            {
                for ( uHEX ic = 0; ic < it->pOffsets.size(); ic++ )
                {
                    uHEX32 HexOldProtect = 0;
                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , PAGE_EXECUTE_READWRITE , &HexOldProtect );

                    for ( int i = 0; i < OpCodes.size(); i++ )
                    {
                        ( ( Bytes ) it->pOffsets[ ic ] )[ i ] = OpCodes[ i ];
                    }

                    N_VirtualMemory::VirtualModifyProtectionFlags( it->pOffsets[ ic ] , pCurrentProcess->pProcess , OpCodes.size() , HexOldProtect );
                }
            }

            if ( bRevertF9 )
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "AirDash enabled.\n" ) );
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "AirDash disabled. \n" ) );
            }

            bRevertF9 = !bRevertF9;
        }

        if ( GetAsyncKeyState( VK_F10 ) )
        {
            *( float* ) ( 0x14160E6D8 ) = ( float ) _wtof( N_Console::Input( TEXT( "Time? (0 to INFINITE)\n" ) ).c_str() );
        }

        //  *( float* ) ( 0x14D0BF70 ) = 3.0f;

       //  *( float* ) ( 0x141554B0 ) = 3.0f;

        /*
        <?xml version="1.0" encoding="utf-8"?>
        <CheatTable>
        <CheatEntries>
        <CheatEntry>
        <ID>47065</ID>
        <Description>"2B AOB"</Description>
        <LastState Value="1F 91 DF 42 89 60 1E 42 D9 84" RealAddress="140BFA70"/>
        <ShowAsHex>1</ShowAsHex>
        <VariableType>Array of byte</VariableType>
        <ByteLength>10</ByteLength>
        <Address>"NieRAutomata.exe"+016053E8</Address>
        <Offsets>
        <Offset>50</Offset>
        </Offsets>
        <CheatEntries>
        <CheatEntry>
        <ID>47034</ID>
        <Description>"2B X"</Description>
        <LastState Value="111.7834396" RealAddress="140BFA70"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+016053E8</Address>
        <Offsets>
        <Offset>50</Offset>
        </Offsets>
        </CheatEntry>
        <CheatEntry>
        <ID>47035</ID>
        <Description>"2B Y"</Description>
        <LastState Value="522.0757446" RealAddress="140BFA78"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+016053E8</Address>
        <Offsets>
        <Offset>58</Offset>
        </Offsets>
        </CheatEntry>
        <CheatEntry>
        <ID>47036</ID>
        <Description>"2B Z"</Description>
        <LastState Value="39.59427261" RealAddress="140BFA74"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+016053E8</Address>
        <Offsets>
        <Offset>54</Offset>
        </Offsets>
        </CheatEntry>
        <CheatEntry>
        <ID>47076</ID>
        <Description>"Extra pointers for 2B's coordinates"</Description>
        <Options moHideChildren="1"/>
        <LastState Value="" RealAddress="00000000"/>
        <GroupHeader>1</GroupHeader>
        <CheatEntries>
        <CheatEntry>
        <ID>47073</ID>
        <Description>"2B Z"</Description>
        <LastState Value="39.59427261" RealAddress="140BFA74"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+016053E8</Address>
        <Offsets>
        <Offset>54</Offset>
        </Offsets>
        </CheatEntry>
        <CheatEntry>
        <ID>47074</ID>
        <Description>"2B Z"</Description>
        <LastState Value="39.59427261" RealAddress="140BFA74"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+016053F0</Address>
        <Offsets>
        <Offset>54</Offset>
        </Offsets>
        </CheatEntry>
        <CheatEntry>
        <ID>47075</ID>
        <Description>"2B Z"</Description>
        <LastState Value="39.59427261" RealAddress="140BFA74"/>
        <VariableType>Float</VariableType>
        <Address>"NieRAutomata.exe"+01605680</Address>
        <Offsets>
        <Offset>54</Offset>
        </Offsets>
        </CheatEntry>
        </CheatEntries>
        </CheatEntry>
        <CheatEntry>
        <ID>47118</ID>
        <Description>"Info"</Description>
        <LastState/>
        <VariableType>Auto Assembler Script</VariableType>
        <AssemblerScript>{
        EXP = Funds + 81B0

        Desert camp
        00 00 2A C3 00 00 40 41 00 00
        Desert center
        00 40 7E C4 00 00 80 C0 00 80
        Desert housing complex
        00 00 DC C2 00 00 A6 C2 00 00
        Desert oil field
        00 00 61 C4 00 00 10 C1 00 00
        Factory entrance
        00 00 D7 C3 00 00 98 C1 00 00
        Resistance camp
        00 00 7A 43 00 00 20 41 00 00
        Start
        00 00 DC C2 00 00 78 42 00 00

        Resistance Camp Z coordinates:
        Ground in front of the access point: 9.482
        On top of the truck's trunk: 10.93

        Normal FOV is 0.87266
        }
        [ENABLE]
        [DISABLE]
        </AssemblerScript>
        </CheatEntry>
        </CheatEntries>
        </CheatEntry>
        </CheatEntries>
        </CheatTable>
        */
        /*
        <?xml version="1.0" encoding="utf-8"?>
        <CheatTable>
        <CheatEntries>
        <CheatEntry>
        <ID>900</ID>
        <Description>"Sprint Speed Modifier"</Description>
        <Options moHideChildren="1"/>
        <LastState/>
        <VariableType>Auto Assembler Script</VariableType>
        <AssemblerScript>[ENABLE]

        aobscanmodule(SprintSpeedAOB,NieRAutomata.exe,F3 0F 11 B3 90 1A 00 00) // should be unique
        alloc(newmem,$1000,"NieRAutomata.exe"+1B8931)

        label(code)
        label(return)
        label(SprintMod)
        registersymbol(SprintMod)

        newmem:

        code:
        push eax
        mov eax,[SprintMod]
        mov [rbx+00001A90],eax
        pop eax
        jmp return

        SprintMod:
        dd (float)3

        SprintSpeedAOB:
        jmp newmem
        nop
        nop
        nop
        return:
        registersymbol(SprintSpeedAOB)

        [DISABLE]

        SprintSpeedAOB:
        db F3 0F 11 B3 90 1A 00 00

        unregistersymbol(SprintSpeedAOB)
        unregistersymbol(SprintMod)
        dealloc(newmem)

        {
        // ORIGINAL CODE - INJECTION POINT: "NieRAutomata.exe"+1B8931

        "NieRAutomata.exe"+1B8900: F3 0F 10 B3 0C 71 01 00        -  movss xmm6,[rbx+0001710C]
        "NieRAutomata.exe"+1B8908: 83 BB 80 6E 01 00 05           -  cmp dword ptr [rbx+00016E80],05
        "NieRAutomata.exe"+1B890F: 75 05                          -  jne NieRAutomata.exe+1B8916
        "NieRAutomata.exe"+1B8911: F3 41 0F 58 F3                 -  addss xmm6,xmm11
        "NieRAutomata.exe"+1B8916: F3 0F 10 83 90 1A 00 00        -  movss xmm0,[rbx+00001A90]
        "NieRAutomata.exe"+1B891E: 48 8B 03                       -  mov rax,[rbx]
        "NieRAutomata.exe"+1B8921: 48 8B CB                       -  mov rcx,rbx
        "NieRAutomata.exe"+1B8924: F3 0F 5C F0                    -  subss xmm6,xmm0
        "NieRAutomata.exe"+1B8928: F3 41 0F 59 F1                 -  mulss xmm6,xmm9
        "NieRAutomata.exe"+1B892D: F3 0F 58 F0                    -  addss xmm6,xmm0
        // ---------- INJECTING HERE ----------
        "NieRAutomata.exe"+1B8931: F3 0F 11 B3 90 1A 00 00        -  movss [rbx+00001A90],xmm6
        // ---------- DONE INJECTING  ----------
        "NieRAutomata.exe"+1B8939: FF 90 50 03 00 00              -  call qword ptr [rax+00000350]
        "NieRAutomata.exe"+1B893F: 85 C0                          -  test eax,eax
        "NieRAutomata.exe"+1B8941: 75 20                          -  jne NieRAutomata.exe+1B8963
        "NieRAutomata.exe"+1B8943: 83 BB 78 64 01 00 01           -  cmp dword ptr [rbx+00016478],01
        "NieRAutomata.exe"+1B894A: 75 17                          -  jne NieRAutomata.exe+1B8963
        "NieRAutomata.exe"+1B894C: 48 8B CB                       -  mov rcx,rbx
        "NieRAutomata.exe"+1B894F: E8 CC CB 08 00                 -  call NieRAutomata.exe+245520
        "NieRAutomata.exe"+1B8954: 48 85 C0                       -  test rax,rax
        "NieRAutomata.exe"+1B8957: 74 0A                          -  je NieRAutomata.exe+1B8963
        "NieRAutomata.exe"+1B8959: C7 83 90 1A 00 00 00 00 80 3F  -  mov [rbx+00001A90],3F800000
        }
        </AssemblerScript>
        <CheatEntries>
        <CheatEntry>
        <ID>901</ID>
        <Description>"Speed Modifier"</Description>
        <VariableType>Float</VariableType>
        <Address>SprintMod</Address>
        </CheatEntry>
        </CheatEntries>
        </CheatEntry>
        </CheatEntries>
        </CheatTable>
*/
        /*
        <?xml version="1.0" encoding="utf-8"?>
<CheatTable>
  <CheatEntries>
    <CheatEntry>
      <ID>47007</ID>
      <Description>"Distance (Combat) (10)"</Description>
      <LastState Value="10" RealAddress="1419856F0"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>1419856F0</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>942</ID>
      <Description>"Distance (Standard) (10)"</Description>
      <LastState Value="10" RealAddress="1419856EC"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>NieRAutomata.exe+19856EC</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47013</ID>
      <Description>"Free Enemy Tracking (6)"</Description>
      <LastState Value="6" RealAddress="141985704"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>141985704</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47012</ID>
      <Description>"Horizontal Auto Adjust (5)"</Description>
      <LastState Value="5" RealAddress="1419856FC"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>1419856FC</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47008</ID>
      <Description>"Horizontal Rotation Speed (8)"</Description>
      <LastState Value="8" RealAddress="1419856F8"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>NieRAutomata.exe+19856F8</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47015</ID>
      <Description>"Locked Enemy Tracking (8)"</Description>
      <LastState Value="8" RealAddress="141985714"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>141985714</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47014</ID>
      <Description>"Pursuit Speed (8)"</Description>
      <LastState Value="8" RealAddress="141985710"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>141985710</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47017</ID>
      <Description>"Screen Brightness"</Description>
      <LastState Value="5" RealAddress="1419856DC"/>
      <ShowAsSigned>1</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>1419856DC</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47011</ID>
      <Description>"Vertical Auto Adjust (5)"</Description>
      <LastState Value="5" RealAddress="141985700"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>141985700</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47009</ID>
      <Description>"Vertical Rotation Speed (6)"</Description>
      <LastState Value="6" RealAddress="1419856F4"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>1419856F4</Address>
    </CheatEntry>
    <CheatEntry>
      <ID>47010</ID>
      <Description>"Zoom Speed (8)"</Description>
      <LastState Value="8" RealAddress="141985708"/>
      <ShowAsSigned>0</ShowAsSigned>
      <VariableType>4 Bytes</VariableType>
      <Address>141985708</Address>
    </CheatEntry>
  </CheatEntries>
</CheatTable>

        */

        if ( GetAsyncKeyState( VK_INSERT ) )
        {
            //N_Hook::UnInit();
            CONSOLEDEBUG( TEXT( "EXITING Thread\n" ) );
            N_Console::Close();
            N_Console::WriteLog();
        }

        Sleep( 200 );
    }

    return nullptr;
}

Pointer __stdcall DllMain( Pointer pModule , Pointer pReason , Pointer pReserved )
{
    //DisableThreadLibraryCalls( ( HMODULE ) pModule );
    // If the dll is attached to the processus we can start doing things.
    // We must create a thread inside the dll because the loader of the dll would be stuck in some cases, it would be waiting for the thread finishing so we avoid that.
    HANDLE hThread = nullptr;

    S_Routine *SRoutine = new S_Routine( pModule , pReserved );

    if ( ( HEX ) pReason == DLL_PROCESS_ATTACH )
    {
        N_Console::Open();

        if ( !SRoutine->bManualMapped )
            hThread = CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) _RoutineHack , ( Pointer ) SRoutine , 0 , nullptr );
        else
            return  _RoutineHack( SRoutine );

        return nullptr;
    }

    return nullptr;
}

__pragma( warning( pop ) )