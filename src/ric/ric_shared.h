// SPDX-License-Identifier: AGPL-3.0-or-later
//
// This contains enums and other declarations that are shared between Player and
// Boss Richter.

#ifndef RIC_SHARED_H
#define RIC_SHARED_H

enum RicInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
#if defined(MOD_MARIA_SAT)
    // Saturn Maria: a jump in the air (her double jump; MariaCheckInput,
    // Saturn 060AAA68)
    CHECK_DOUBLE_JUMP = 0x20,
#endif
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
#if defined(MOD_MARIA_SAT)
    // Saturn Maria: R, her backdash (060AAA68 -> 060A9E40; standing,
    // walking and running)
    CHECK_BACKDASH = 0x80000,
#endif
};

enum RicTimers {
    PL_T_POISON,
    PL_T_CURSE,
    PL_T_2,
    PL_T_3,
    PL_T_4,
    PL_T_5,
    PL_T_6,
    PL_T_7,
    PL_T_8,
    PL_T_ATTACK,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE_SCENE, // "dying" in the prologue
    PL_T_INVINCIBLE,
    PL_T_AFTERIMAGE_DISABLE,
};

enum RicBlueprints {
    BP_SKID_SMOKE,
    BP_SMOKE_PUFF,
    BP_SUBWPN_CROSS,
    BP_SUBWPN_CROSS_PARTICLES,
    BP_EMBERS,
    BP_5,
    BP_SUBWPN_HOLYWATER,
    BP_HOLYWATER_FIRE,
    BP_HIT_BY_FIRE,
    BP_HOLYWATER_FLAMES,
    BP_WHIP,
    BP_MULTIPLE_EMBERS,
    BP_HYDROSTORM,
    BP_CRASH_CROSS,
    BP_CRASH_CROSSES_ONLY,
    BP_NOT_IMPLEMENTED_1,
    // 0x10
    BP_NOT_IMPLEMENTED_2,
    BP_ARM_BRANDISH_WHIP,
    BP_18,
    BP_AXE,
    BP_20,
    BP_NOT_IMPLEMENTED_3,
    BP_REVIVAL_COLUMN,
    BP_MARIA_POWERS_APPLIED,
    BP_SLIDE,
    BP_25,
    BP_BLADE_DASH,
    BP_BLUE_CIRCLE,
    BP_BLUE_SPHERE,
    BP_MARIA,
    BP_MARIA_POWERS_INVOKED,
    BP_31,
    // 0x20
    BP_NOT_IMPLEMENTED_4,
    BP_RIC_BLINK,
    BP_CRASH_CROSS_PARTICLES,
    BP_35,
    BP_36,
    BP_37,
    BP_38,
    BP_39,
    BP_HOLYWATER_GLASS,
    BP_CRASH_AXE,
    BP_42,
    BP_SUBWPN_DAGGER,
    BP_CRASH_DAGGER,
    BP_HIGH_JUMP,
    BP_HIT_BY_CUT,
    BP_HIT_BY_ICE,
    // 0x30
    BP_HIT_BY_THUNDER,
    BP_VIBHUTI,
    BP_REBOUND_STONE,
    BP_AGUNEA,
    BP_AGUNEA_HIT_ENEMY,
    BP_DEATH_BY_FIRE,
    BP_CRASH_VITHUBI,
    BP_VITHUBI_CRASH_CLOUD,
    BP_CRASH_REBOUND_STONE,
    BP_57,
    BP_CRASH_REBOUND_STONE_EXPLOSION,
    BP_CRASH_BIBLE,
    BP_CRASH_BIBLE_BEAM,
    BP_BIBLE,
    BP_BIBLE_TRAIL,
    BP_SUBWPN_STOPWATCH,
    // 0x40
    BP_STOPWATCH_CIRCLE,
    BP_CRASH_STOPWATCH,
    BP_66,
    BP_CRASH_AGUNEA,
    BP_CRASH_AGUNEA_THUNDER,
    BP_CRASH_REBOUND_STONE_PARTICLES,
    BP_HIT_BY_DARK,
    BP_HIT_BY_HOLY,
    BP_AGUNEA_THUNDER,
    BP_CRASH_STOPWATCH_LIGHTNING,
    BP_SMOKE_PUFF_2,
    BP_SKID_SMOKE_2,
    BP_SKID_SMOKE_3,
    BP_TELEPORT,
#if defined(MOD_MARIA_SAT)
    // Saturn Maria's own blueprints (MARIA.PRG 79-104; mar_attacks.h)
    BP_MAR_SHOT, // 79 Square: her shot (060B9404)
    BP_MAR_KICK, // 80 Triangle: her kick hitbox (060AD0E8)
    BP_MAR_DIVE, // 81 dive kick hitbox (060AD248)
    BP_MAR_82,
    BP_MAR_KNUCKLE,  // 83 the command specials (mar_specials.h)
    BP_MAR_GENBU,    // 84
    BP_MAR_BYAKKO,   // 85
    BP_MAR_SEIRYU,   // 86
    BP_MAR_SUZAKU,   // 87
    BP_MAR_BEAST,    // 88 one guardian beast (params: 1-4)
    BP_MAR_FLAME,    // 89
    BP_MAR_DRAGON,   // 90 (params: segment)
    BP_MAR_STAR,     // 91 (params: frames to wait)
    BP_MAR_TRAIL,    // 92 (params: frame)
    BP_MAR_CHARGE_1, // 93 charged shot level 1 (060B9B88)
    BP_MAR_CHARGE_2, // 94 level 2 (060B9D88) and its trail
    BP_MAR_CHARGE_3, // 95 level 3, the laser (060B96C0)
    BP_MAR_SPARK,    // 96 the laser's sparks (060B99A8)
    BP_MAR_97,
    BP_MAR_ASH,       // 98 the puff a vibhuti throw leaves (060B18C8)
    BP_MAR_CHARGED,   // 99 fully charged (060BD150)
    BP_MAR_AURA,      // 100 its diamonds (060BD244)
    BP_MAR_COUNTDOWN, // 101 Four Beasts countdown
    BP_MAR_BEASTS,    // 102 Four Beasts
    BP_MAR_103,
    BP_MAR_104,
#endif
    NUM_BLUEPRINTS,
};

enum RicSubweapons {
    PL_W_NONE,
    PL_W_DAGGER,
    PL_W_AXE,
    PL_W_HOLYWATER,
    PL_W_CROSS,
    PL_W_BIBLE,
    PL_W_STOPWATCH,
    PL_W_REBNDSTONE,
    PL_W_VIBHUTI,
    PL_W_AGUNEA,
    PL_W_10,
    PL_W_HOLYWATER_FLAMES,
    PL_W_CRASH_CROSS,
    PL_W_CRASH_CROSS_BEAM,
    PL_W_WHIP,
    PL_W_15,
    PL_W_HYDROSTORM,
    PL_W_BIBLE_BEAM,
    PL_W_KICK,
    PL_W_19,
    PL_W_20,
    PL_W_21,
    PL_W_HIGHJUMP,
    PL_W_23,
    PL_W_CRASH_VIBHUTI,
    PL_W_CRASH_REBOUND_STONE,
    PL_W_CRASH_AGUNEA,
    PL_W_27,
    PL_W_28,
    PL_W_CRASH_REBOUND_EXPLOSION,
    PL_W_30,
    NUM_WEAPONS,
};

#endif // RIC_SHARED_H
