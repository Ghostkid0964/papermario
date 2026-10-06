#!/bin/bash
export PATH=$PATH:/opt/devkitpro/devkitARM/bin
mkdir -p port3ds/gobj

FLAGS="-std=gnu99 -c -w -fcommon -include stddef.h -I/opt/devkitpro/libctru/include -I ver/us/include -I ver/us/build/include -I include -I include/PR -I src -I assets/us -DVERSION=us -DVERSION_US -D_LANGUAGE_C -DF3DEX_GBI_2 -D_FINALROM -D_MIPS_SZLONG=32 -DOLD_GCC -Wno-error=implicit-function-declaration -Wno-error=return-mismatch -march=armv6k -mtune=mpcore -mfloat-abi=hard"

cp include/include_asset.h /tmp/ia.bak
sed -i 's/@object/%object/g' include/include_asset.h

rm -f port3ds/gobj/*.o

# Exclude MIPS assembly/OS/GCC sources and non-US language files
SOURCES="$(find port3ds -name "*.c") $(find src -name "*.c" ! -name "*.inc.c" ! -name "pause_gfx_*" ! -name "*_fr.c" ! -name "*_es.c" ! -name "*_de.c" ! -name "*_en_de.c" ! -name "filemenu_selectlanguage.c" ! -path "src/audio/core/system.c" ! -path "src/os/*" ! -path "src/gcc/*")"

for f in $SOURCES; do
  arm-none-eabi-gcc $FLAGS $f -o port3ds/gobj/$(basename $f).o 2>/dev/null || echo "FAIL $f"
done

cp /tmp/ia.bak include/include_asset.h

arm-none-eabi-ar rcs port3ds/libgame.a port3ds/gobj/*.o
ls -lh port3ds/libgame.a
