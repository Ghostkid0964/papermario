#include <3ds.h>
#include <stdio.h>
#include "common.h"

// Standard Paper Mario decompilation entry point
extern void boot_main(void* arg);

int main(int argc, char** argv) {
    // 1. Initialize 3DS hardware systems
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL);

    printf("Initializing Paper Mario engine...\n");

    // 2. Call the decomp engine boot routine
    boot_main(NULL);

    printf("Engine loaded! Running main loop...\n");

    // 3. Main 3DS loop
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break; // Exit to Homebrew Menu on Start

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
