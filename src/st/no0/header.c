// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "../pfn_entity_update.h"

extern RoomHeader rooms[];
extern s16** spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern u_long** gfxBanks[];
#if defined(MOD_SATURN)
// Saturn port: room tables with the Cursed Prison's loading room and
// transition (src/st/no0/mod_rooms.h,
// mods/sotn-ultimate/tools/gen_prs_links.py)
extern RoomHeader g_ModRooms[];
extern RoomDef g_ModRoomsLayers[];
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
    .spriteBanks = (SpriteParts**)spriteBanks,
    .cluts = cluts,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
#if defined(MOD_SATURN)
    .tileLayers = g_ModRoomsLayers,
#else
    .tileLayers = rooms_layers,
#endif
    .gfxBanks = (GfxBank**)gfxBanks,
    .UpdateStageEntities = UpdateStageEntities,
};

#ifdef VERSION_US
#include <gen/sprite_banks.h>
#include <gen/palette_def.h>
#include <gen/layers.h>
#include <gen/graphics_banks.h>
#endif
