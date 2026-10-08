#!/bin/bash
export PATH=$PATH:/opt/devkitpro/devkitARM/bin
mkdir -p port3ds/gobj

FLAGS="-std=gnu99 -c -w -mword-relocations -fcommon -include stddef.h -I ver/us/include -I ver/us/build/include -I include -I include/PR -I src -I assets/us -DVERSION=us -DVERSION_US -D_LANGUAGE_C -DF3DEX_GBI_2 -D_FINALROM -D_MIPS_SZLONG=32 -DOLD_GCC -Wno-error=implicit-function-declaration -Wno-error=return-mismatch -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp -mtp=soft"

cp include/include_asset.h /tmp/ia.bak
sed -i 's/@object/%object/g' include/include_asset.h

rm -f port3ds/gobj/*.o
: > port3ds/build_errors.log

SRC=$(ls src/*.c | grep -v -E "titlemenu|level_up_letters|starpoint_")
SUB=$(find src/common src/entity src/audio src/evt src/pause src/filemenu src/battle/move src/battle/action_cmd src/battle/area/flo2 -name "*.c" ! -name "*.inc.c" ! -name "pause_gfx_*" ! -name "filemenu_selectlanguage.c" ! -path "src/audio/core/system.c")
EXTRA=$(ls src/world/*.c src/world/action/*.c src/world/partner/*.c src/battle/partner/*.c $(ls src/battle/*.c | grep -v "16C8E0") src/effects/*.c 2>/dev/null)

ALL_FILES="port3ds/game/ultra_stubs.c port3ds/game/boot3ds_init.c $SRC $SUB $EXTRA"

echo "Compiling game objects..."
for f in $ALL_FILES; do
    obj_name=$(echo "$f" | tr '/' '_').o
    arm-none-eabi-gcc $FLAGS "$f" -o "port3ds/gobj/$obj_name" 2>>port3ds/build_errors.log || echo "FAIL $f"
done

cp /tmp/ia.bak include/include_asset.h

echo "Archiving libgame.a..."
rm -f port3ds/lib/libgame.a
arm-none-eabi-ar rcs port3ds/lib/libgame.a port3ds/gobj/*.o
ls -lh port3ds/lib/libgame.a
