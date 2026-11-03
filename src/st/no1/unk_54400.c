// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static u8 anim0[] = {6, 5, 6, 6, 6, 7, 6, 8, 6, 1, 0, 0}; // unused
static u8 anim1[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 0, 0,
};

static s16 D_us_801831F4[] = {0, 3, 4, 3, 0, -3, -4, -3};
static s16 D_us_80183204[] = {-16, -12, 0, 12, 16, 12, 0, -12};

#if defined(MOD_OUTER_WALL_GHOST)
#include "../../../mods/sotn-ultimate/src/castle/unk_54400_mod_ghost.h"
#endif

void func_us_801D4558(Entity* self) {
    Entity* tempEntity;
    s16 tempVar;
    s16 posX, posY;

#if defined(MOD_OUTER_WALL_GHOST)
    GhostLoadGfx(self->step == 0);
#endif
    if (self->flags & FLAG_DEAD) {
        EntityExplosionSpawn(0, 0);
        return;
    }
    if (self->hitParams && self->step != 4) {
        self->step = 4;
        self->step_s = 0;
    }
    tempEntity = &PLAYER;
    if ((tempEntity->posX.i.hi - self->posX.i.hi) > 0) {
        self->facingLeft = true;
    } else {
        self->facingLeft = false;
    }
    switch (self->step) {
    case 0:
#if defined(MOD_OUTER_WALL_GHOST)
        // mod: params bits 0-2 = the weathers it appears in (1 rain, 2 clear,
        // 4 fog: g_CastleFlags[NO1_WEATHER] & 0x7F is 0 / 1 / 2, as the sky
        // and rain entities read it); 0 = every weather
        // Relic gate: every ghost stays dormant (step 1, scale 0, no hitbox)
        // until Soul of Wolf is found. params bit 8 (A, the relic nook): if
        // the relic is not found yet when it spawns, it skips the weather
        // rule and fades in the moment the relic is collected (unk84 = 1),
        // wherever the player is; otherwise the weather rule applies.
        // Once the Ghost Card is found the ghosts are gone (it is your ally).
        if (g_Status.relics[RELIC_GHOST_CARD] & RELIC_FLAG_FOUND) {
            DestroyEntity(self);
            return;
        }
        if ((self->params & 0x100) &&
            !(g_Status.relics[RELIC_SOUL_OF_WOLF] & RELIC_FLAG_FOUND)) {
            self->ext.et_801D4558.unk84 = 1;
        } else if ((self->params & 7) &&
                   !(self->params & (1 << (g_CastleFlags[NO1_WEATHER] & 3)))) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(D_us_80180B18);
#if defined(MOD_OUTER_WALL_GHOST)
        self->unk5A = GHOST_UNK5A; // the copy at 352,256 (see GhostLoadGfx)
#endif
        self->ext.et_801D4558.unk80 = self->hitboxState;
        self->hitboxState = 0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;

        self->scaleX = 0;
        self->scaleY = 0;
        self->ext.et_801D4558.unk7D = 0;
        self->blendMode = BLEND_TRANSP;
        break;

    case 1:
#if defined(MOD_OUTER_WALL_GHOST)
        // dormant until Soul of Wolf is found; never with the Ghost Card
        if (!(g_Status.relics[RELIC_SOUL_OF_WOLF] & RELIC_FLAG_FOUND) ||
            (g_Status.relics[RELIC_GHOST_CARD] & RELIC_FLAG_FOUND)) {
            break;
        }
        if (self->ext.et_801D4558.unk84) { // A: relic found this visit
            self->step++;
            self->ext.et_801D4558.unk7C = 0;
            break;
        }
#endif
        tempVar = (s16)self->params & 0xF8;
        if (tempVar > GetDistanceToPlayerX() &&
            tempVar > GetDistanceToPlayerY()) {
            self->step++;
            self->ext.et_801D4558.unk7C = 0;
        }
        break;

    case 2:
        AnimateEntity(anim1, self);
        self->ext.et_801D4558.unk7C++;
        self->scaleX += 8;
        self->scaleY += 8;
        if (self->ext.et_801D4558.unk7C == 0x20) {
            self->hitboxState = 2;
            self->drawFlags = ENTITY_DEFAULT;
        }
        if (self->ext.et_801D4558.unk7C == 0x28) {
            self->hitboxState = self->ext.et_801D4558.unk80;
            SetStep(3);
            self->ext.et_801D4558.unk82 = 0;
            self->drawFlags = ENTITY_DEFAULT;
        }
        break;

    case 3:
        AnimateEntity(anim1, self);
        SetEntityVelocityFromAngle(
            self->ext.et_801D4558.unkAC, self->ext.et_801D4558.unkB0);
        self->velocityX >>= 8;
        self->velocityY >>= 8;
        MoveEntity();
        if (!self->ext.et_801D4558.unk82) {
            self->ext.et_801D4558.unk84 = D_us_80183204[Random() & 7];
            self->ext.et_801D4558.unk86 = D_us_80183204[Random() & 7];
            self->ext.et_801D4558.unk82 = (Random() & 0x1F) + 0x20;
        } else {
            self->ext.et_801D4558.unk82--;
        }
        posX = tempEntity->posX.i.hi + self->ext.et_801D4558.unk84;
        posY = tempEntity->posY.i.hi + self->ext.et_801D4558.unk86;
        self->ext.et_801D4558.unkAC = AdjustValueWithinThreshold(
            1, self->ext.et_801D4558.unkAC,
            GetAnglePointToEntityShifted(posX, posY));
        self->ext.et_801D4558.unkB0 += 0x40;
        if (self->ext.et_801D4558.unkB0 > 0x1800) {
            self->ext.et_801D4558.unkB0 = 0x1800;
        }
        break;

    case 4:
        AnimateEntity(anim1, self);
        if (self->step_s) {
            MoveEntity();
            if (!--self->ext.et_801D4558.unk7C) {
                self->step = 3;
                self->ext.et_801D4558.unkB0 = 0;
            }
        } else {
            self->ext.et_801D4558.unkAC =
                GetAngleBetweenEntitiesShifted(tempEntity, self);
            SetEntityVelocityFromAngle(self->ext.et_801D4558.unkAC, 0x18);
            self->ext.et_801D4558.unk7C = 0x14;
            self->step_s++;
        }
        break;
    }
    if (self->step > 1) {
        self->ext.et_801D4558.unk7D++;
        if ((self->ext.et_801D4558.unk7D & 3) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_52, tempEntity);
                tempVar = Random();
                tempEntity->posX.i.hi += D_us_801831F4[tempVar & 7];
                tempEntity->posY.i.hi += D_us_801831F4[(tempVar - 2) & 7];
            }
        }
    }
}

static u8 anim2[] = {
    2,  9, 2,  10, 2,  11, 2,  12, 2,  13, 2,  14, 2,
    15, 2, 16, 2,  17, 2,  18, 2,  19, 2,  20, -1, 0,
};

void func_us_801D4950(Entity* self) {
#if defined(MOD_OUTER_WALL_GHOST)
    GhostLoadGfx(false);
#endif
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B18);
#if defined(MOD_OUTER_WALL_GHOST)
        self->unk5A = GHOST_UNK5A;
#endif
        self->blendMode = BLEND_TRANSP;
        self->hitboxState = 0;
        break;

    case 1:
        if (AnimateEntity(anim2, self) == 0) {
            DestroyEntity(self);
        }
        self->posY.i.hi--;
        break;
    }
}
