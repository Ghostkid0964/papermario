#include <3ds.h>
#include <stdio.h>

int main(void) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    printf("Paper Mario 3DS port\n");
    while (aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        if (hidKeysDown() & KEY_START) break;
    }
    gfxExit();
    return 0;
}
