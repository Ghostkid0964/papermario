#!/bin/bash
# Run inside the dkp3ds container from /project
export PATH=$PATH:/opt/devkitpro/devkitARM/bin
mkdir -p port3ds/gobj
FLAGS="-std=gnu99 -c -w -include stddef.h -I ver/us/include -I ver/us/build/include -I include -I include/PR -I src -I assets/us -DVERSION=us -DVERSION_US -D_LANGUAGE_C -DF3DEX_GBI_2 -D_FINALROM -D_MIPS_SZLONG=32 -DOLD_GCC -Wno-error=implicit-function-declaration -Wno-error=return-mismatch -march=armv6k -mtune=mpcore -mfloat-abi=hard"
cp include/include_asset.h /tmp/ia.bak
sed -i 's/@object/%object/g' include/include_asset.h
rm -f port3ds/gobj/*.o
for f in port3ds/game/ultra_stubs.c $(ls src/*.c | grep -v -E "titlemenu|level_up_letters|starpoint_") $(find src/common src/entity src/audio src/evt src/pause src/filemenu -name "*.c" ! -name "*.inc.c" ! -name "pause_gfx_*" ! -name "filemenu_selectlanguage.c" ! -path "src/audio/core/system.c"); do
  arm-none-eabi-gcc $FLAGS $f -o port3ds/gobj/$(basename $f).o || echo "FAIL $f"
done
cp /tmp/ia.bak include/include_asset.h
arm-none-eabi-ar rcs port3ds/libgame.a port3ds/gobj/*.o
ls -l port3ds/libgame.a
