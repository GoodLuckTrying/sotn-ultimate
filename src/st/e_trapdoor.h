// SPDX-License-Identifier: AGPL-3.0-or-later
static s32 g_TrapDoorFlag = 0; // 0 = Closed, 1 = Open

static u8 trapdoor_anim[] = {1, 27, 6, 28, 6, 29, 129, 30, 255};

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
#if defined(MOD_SATURN)
// Saturn rule (STAGE_01 0x060DF308 / STAGE_0X 0x060E24A4): the door is open
// in NP3 always, and in NO3 once Death has robbed Alucard. Closed doors open
// from below only; there is no hit check.
static s32 ModTrapDoorIsOpen(void) {
#if defined(STAGE_IS_NP3)
    return 1;
#else
    return g_CastleFlags[IVE_BEEN_ROBBED] &&
           g_PlayableCharacter == PLAYER_ALUCARD;
#endif
}

static void ModTrapDoorSetColl(s32 open) {
    if (open) {
        g_Tilemap.fg[0xA8E / 2] = 0x6C8;
        g_Tilemap.fg[0xA90 / 2] = 0x6C9;
    } else {
        g_Tilemap.fg[0xA8E / 2] = 0x129;
        g_Tilemap.fg[0xA90 / 2] = 0x132;
    }
}

void EntityTrapDoor(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 27;
        self->zPriority = 0x6A;
        self->hitboxState = 1;
        self->hitboxWidth = 16;
        self->hitboxHeight = 4;
        if (ModTrapDoorIsOpen()) {
            self->animCurFrame = 30;
            ModTrapDoorSetColl(1);
            self->step = 128;
            break;
        }
        ModTrapDoorSetColl(0);
        if (PLAYER.posY.val >= self->posY.val) {
            ModTrapDoorSetColl(1);
            self->step = 2;
        } else {
            self->step = 1;
        }
        break;

    case 1:
        if (ModTrapDoorIsOpen()) {
            self->step = 2;
        }
        break;

    case 2:
        AnimateEntity(trapdoor_anim, self);
        break;
    }
    (void)g_TrapDoorFlag;
}
#else
void EntityTrapDoor(Entity* self) {
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 27;
        self->zPriority = 0x6A;
        self->hitboxState = 1;
        self->hitboxWidth = 16;
        self->hitboxHeight = 4;

        if (g_TrapDoorFlag == 0) {
            player = &PLAYER;
            if (player->posY.val < self->posY.val) {
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
                DestroyEntity(self);
                break;
            }
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
        } else {
            self->animCurFrame = 30;
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
            self->step = 128;
        }

    case 1:
        if (self->hitFlags) {
            g_TrapDoorFlag = 1;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(trapdoor_anim, self);
        break;
    }
}
#endif
