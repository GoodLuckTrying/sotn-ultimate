// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

#include "../e_red_door.h"

#if defined(MOD_SATURN)
// Saturn port: layout copy with the mod's entities. It lives here because
// this file's rodata is linked after the stage's data section, which
// cutscene scripts address directly and so must not move.
#include "mod_layout.h"
#include "mod_layout2.h"
#include "mod_rooms.h"
#endif
