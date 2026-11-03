// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);
#if defined(MOD_SATURN)
// Saturn port: room tables with the sixth warp room (61,18), next to the Hell
// Garden (src/st/rwrp/mod_rooms.h, mods/sotn-ultimate/tools/gen_mod_rooms.py;
// rodata copies in e_red_door.c)
extern RoomHeader g_ModRooms[];
extern RoomDef g_ModRoomsLayers[];
#define MOD_ROOMS g_ModRooms
#define MOD_ROOMS_LAYERS g_ModRoomsLayers
#else
#define MOD_ROOMS rooms
#define MOD_ROOMS_LAYERS rooms_layers
#endif

Overlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = MOD_ROOMS,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = MOD_ROOMS_LAYERS,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
    .unk2C = NULL,
    .unk30 = NULL,
    .unk34 = NULL,
    .unk38 = NULL,
    .StageEndCutScene = NULL,
};
