// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"
#include "../pfn_entity_update.h"

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);
#if defined(MOD_SATURN)
// Saturn port: room tables with the Soul Prison's doorway, loading room and
// transition (src/st/rno0/mod_rooms.h,
// mods/sotn-ultimate/tools/gen_prs_links.py; rodata copies in e_red_door.c)
extern RoomHeader g_ModRooms[];
extern RoomDef g_ModRoomsLayers[];
#define MOD_ROOMS g_ModRooms
#define MOD_ROOMS_LAYERS g_ModRoomsLayers
#else
#define MOD_ROOMS rooms
#define MOD_ROOMS_LAYERS rooms_layers
#endif

AbbreviatedOverlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = MOD_ROOMS,
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = MOD_ROOMS_LAYERS,
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};
