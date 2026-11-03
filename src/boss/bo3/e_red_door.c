// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

#include "../../st/e_red_door.h"

#if defined(MOD_SATURN)
// Saturn port: layout copy with the mod's entities. It lives here because
// this file's rodata is linked after the overlay's data section.
#include "mod_layout.h"
#endif
