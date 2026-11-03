// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#if defined(MOD_SATURN)
// Saturn port: SEL links its own copy of DRA's config tables (equipment,
// relics, spells, enemies...), but no SEL code or data refers to them. The
// mod keeps their data bytes (the retail ones, so SEL's data section and
// every address after it stay retail) and drops their strings, ~15 KB of
// rodata: room for the PSP dub toggle (the ending's PSP script copy, the
// select screen's dub row)
__asm__(".pushsection .data\n"
        ".balign 4\n"
        ".incbin \"disks/us/ST/SEL/SEL.BIN\", 0x25FC, 0x7F10\n"
        ".popsection");
#else
#include "../../config_us.h"
#endif
