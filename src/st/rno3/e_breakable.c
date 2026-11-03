// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"
extern EInit g_EInitBreakable;

static u8 anim_1[] = {4, 1, 4, 2, 0, 0};
static u8 anim_2[] = {4, 0, 4, 0, 0};
static u8* g_eBreakableAnimations[8] = {anim_1, anim_2};
static u8 g_eBreakableHitboxes[8] = {8, 8};
static u8 g_eBreakableExplosionTypes[8] = {0, 0};

static u16 g_eBreakableanimSets[8] = {ANIMSET_DRA(3), ANIMSET_DRA(3)};
static u8 blend_modes[8] = {
    BLEND_TRANSP | BLEND_QUARTER,
    BLEND_TRANSP | BLEND_ADD,
};

// Stripped on PSP
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};

#if defined(MOD_SATURN)
// Saturn port: the shaft's candelabras (type 2), as the Saturn's inverted
// Entrance draws them (RSTAGE01 candle type 3): the Saturn's tall candelabra
// with its glow, hanging from the ceiling (drawn turned around like RNO3's
// own candles). EntityModBreakable is the shared Saturn candle code
// (../e_breakable.h) on rodata copies of the tables with type 2 added; the
// retail tables above stay in the data section.
void EntityModBreakable(Entity* entity);
#define MOD_CANDLE_TYPE 2
#endif

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 12;
#if defined(MOD_SATURN)
    if (breakableType == MOD_CANDLE_TYPE) {
        if (entity->step && entity->hitParams) {
            // it becomes the drop, which is drawn upright
            entity->drawFlags = ENTITY_DEFAULT;
            entity->rotate = ROT(0);
            EntityModBreakable(entity);
            return;
        }
        EntityModBreakable(entity);
        entity->drawFlags = ENTITY_ROTATE;
        entity->rotate = ROT(180);
        return;
    }
#endif
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->hitParams) { // If the candle is destroyed
            Entity* entityDropItem;
            entity->drawFlags = ENTITY_DEFAULT;
            entity->rotate = ROT(0);
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        entity->blendMode = blend_modes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
        entity->drawFlags = ENTITY_ROTATE;
        entity->rotate = ROT(180);
    }
}

#if defined(MOD_SATURN_CASTLE)
#include "../../../mods/sotn-ultimate/src/castle/rno3/e_breakable_mod_sconce.h"
#endif
