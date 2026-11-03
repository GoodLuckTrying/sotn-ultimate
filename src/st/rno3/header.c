// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"
#include "../pfn_entity_update.h"

// common
extern RoomHeader rooms[];
extern SpriteParts* spriteBanks[];
extern u_long* cluts[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
void UpdateStageEntities(void);
#if defined(MOD_SATURN_CASTLE)
#include "../../../mods/sotn-ultimate/src/castle/rno3/header_mod_shaft.h"
#else
#define MOD_ROOMS rooms
#define MOD_ROOMS_LAYERS rooms_layers
#define MOD_SPRITE_BANKS spriteBanks
#define MOD_CLUTS cluts
#define MOD_GFX_BANKS gfxBanks
#endif

AbbreviatedOverlay g_Overlay = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = MOD_ROOMS,
    .spriteBanks = MOD_SPRITE_BANKS,
    .cluts = MOD_CLUTS,
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
    .tileLayers = MOD_ROOMS_LAYERS,
    .gfxBanks = MOD_GFX_BANKS,
    .UpdateStageEntities = UpdateStageEntities,
};
