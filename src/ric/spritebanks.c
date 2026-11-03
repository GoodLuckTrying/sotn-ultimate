// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

#ifdef VERSION_PSP
#include "gen/spritebank3.h"
#endif

#if defined(MOD_MARIA_SAT)
#include "mar_spritebank0.h"
#else
#include "gen/spritebank0.h"
#endif
#include "gen/spritebank1.h"
#include "gen/spritebank2.h"

#ifndef VERSION_PSP
#include "gen/spritebank3.h"
#endif
