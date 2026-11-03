// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern LayoutEntity* entityLayoutHorizontal[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];
#if defined(MOD_SATURN)
// Saturn port: room tables with the shaft extended to the Underground Garden
// (src/st/np3/mod_rooms.h, mods/sotn-ultimate/tools/gen_mod_rooms.py)
extern RoomHeader g_ModRooms[];
extern RoomDef g_ModRoomsLayers[];
// and graphics, sprite and palette tables with the shaft's wall sconce
// (src/st/np3/mod_sconce.h, below)
extern s16** g_ModSpriteBanks[];
extern u_long* g_ModCluts[];
extern u_long** g_ModGfxBanks[];
#endif

AbbreviatedOverlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
#if defined(MOD_SATURN)
    .rooms = g_ModRooms,
#else
    .rooms = rooms,
#endif
#if defined(MOD_SATURN)
    .spriteBanks = g_ModSpriteBanks,
    .cluts = g_ModCluts,
#else
    .spriteBanks = spriteBanks,
    .cluts = cluts,
#endif
    .objLayoutHorizontal = entityLayoutHorizontal,
#if defined(MOD_SATURN)
    .tileLayers = g_ModRoomsLayers,
#else
    .tileLayers = rooms_layers,
#endif
#if defined(MOD_SATURN)
    .gfxBanks = g_ModGfxBanks,
#else
    .gfxBanks = gfxBanks,
#endif
    .UpdateStageEntities = UpdateStageEntities,
};

#include <gen/sprite_banks.h>
#include <gen/palette_def.h>
#include <gen/layers.h>
#include <gen/graphics_banks.h>
