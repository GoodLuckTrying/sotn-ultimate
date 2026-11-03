#!/usr/bin/env python3

import argparse
import json
import os


def patch(config_file_name):
    # Saturn port mod: the dirt bytes are retail alignment junk written at
    # fixed file offsets. The mod moves DRA's data and rodata, so those
    # offsets land on live data (one hit MenuHandle's jump table and
    # crashed the game on closing the menu after a cape change).
    # mods/sotn-ultimate/tools/build_disc.sh sets SOTN_MOD_NO_DIRT.
    if os.environ.get("SOTN_MOD_NO_DIRT"):
        print("dirt: skipped (SOTN_MOD_NO_DIRT)")
        return
    with open(config_file_name, "r") as f:
        patches = json.load(f)
    for patch in patches:
        name = patch["name"]
        with open(name, "r+b") as f:
            for str_offset in patch:
                if not str_offset.startswith("0x"):
                    continue
                offset = int(str_offset[2:], base=16)
                value = patch[str_offset]
                f.seek(offset)
                f.write(bytes([value]))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="given a configuration, patches an existing binary"
    )
    parser.add_argument(
        "config",
        help="File path of the patch configuration",
    )

    args = parser.parse_args()
    patch(args.config)
