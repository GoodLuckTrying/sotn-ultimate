// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 objLayoutId);

extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];

#if defined(MOD_SATURN)
// Saturn port: room tables with the sixth warp room (src/st/wrp/mod_rooms.h,
// mods/sotn-ultimate/tools/gen_mod_rooms.py)
extern RoomHeader g_ModRooms[];
extern RoomDef g_ModRoomsLayers[];
#endif

Overlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
#if defined(MOD_SATURN)
    .rooms = g_ModRooms,
#else
    .rooms = rooms,
#endif
    .spriteBanks = spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = NULL,
#if defined(MOD_SATURN)
    .tileLayers = g_ModRoomsLayers,
#else
    .tileLayers = rooms_layers,
#endif
    .gfxBanks = gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};
