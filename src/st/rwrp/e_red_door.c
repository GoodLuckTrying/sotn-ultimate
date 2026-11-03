// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

#include "../e_red_door.h"

#if defined(MOD_SATURN)
// Saturn port: room table copies and the warp room's layout (rodata, after the
// stage's data section, which must not move)
#include "mod_rooms.h"
#include "mod_layout.h"
#endif
