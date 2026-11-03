// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

#include "../e_red_door.h"

#if defined(MOD_SATURN)
// Saturn port: layout and room table copies (rodata, after the stage's data
// section, which must not move): the Cursed Prison's door
#include "mod_layout.h"
#include "mod_rooms.h"
#endif
