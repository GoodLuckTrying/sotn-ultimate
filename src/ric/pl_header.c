// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

#if defined(MOD_MARIA_SAT)
extern u8* richter_sprites[];
#else
extern u8* richter_sprites[RIC_SPRITE_COUNT];
#endif
void RicMain(void);
void RicInit(u16 params);
void RicUpdatePlayerEntities(void);
void RicGetPlayerSensor(Collider* col);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    RicGetPlayerSensor,
    richter_sprites,
    richter_sprites,
    richter_sprites,
    richter_sprites,
};

#if defined(MOD_MARIA_SAT)
// Saturn port: the Saturn Maria's images
// (mods/sotn-ultimate/tools/gen_mar_assets.py)
#include "mar_sprites.h"
#elif !defined(VERSION_PSP)
#include "gen/richter.h"
#endif
