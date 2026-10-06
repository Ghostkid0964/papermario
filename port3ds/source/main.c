#include <3ds.h>
#include <stdio.h>
#include <string.h>

extern unsigned int osGetCount(void);
extern void nuPiReadRom(u32 romAddr, void *buffer, u32 size);

static FILE *gGameRom;
static long gGameRomSize;

static int plat3ds_rom_open(void) {
    u8 header[4];

    if (gGameRom != NULL) {
        return 1;
    }

    gGameRom = fopen("sdmc:/3ds/papermario/baserom.z64", "rb");
    if (gGameRom == NULL) {
        return 0;
    }

    if (fseek(gGameRom, 0, SEEK_END) != 0) {
        goto fail;
    }
    gGameRomSize = ftell(gGameRom);
    if (gGameRomSize < 0x40 || fseek(gGameRom, 0, SEEK_SET) != 0) {
        goto fail;
    }
    if (fread(header, 1, sizeof(header), gGameRom) != sizeof(header)) {
        goto fail;
    }
    if (header[0] != 0x80 || header[1] != 0x37 || header[2] != 0x12 || header[3] != 0x40) {
        goto fail;
    }

    return 1;

fail:
    fclose(gGameRom);
    gGameRom = NULL;
    gGameRomSize = 0;
    return 0;
}

void nuPiReadRom(u32 romAddr, void *buffer, u32 size) {
    size_t bytesRead;

    if (size == 0) {
        return;
    }
    if (gGameRom == NULL || romAddr > (u32)gGameRomSize ||
        size > (u32)gGameRomSize - romAddr ||
        fseek(gGameRom, (long)romAddr, SEEK_SET) != 0) {
        memset(buffer, 0, size);
        return;
    }

    bytesRead = fread(buffer, 1, size, gGameRom);
    if (bytesRead != size) {
        memset((u8 *)buffer + bytesRead, 0, size - bytesRead);
    }
}

int main(void) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    printf("Paper Mario 3DS port\n");
    printf("osGetCount: %u\n", osGetCount());

    if (plat3ds_rom_open()) {
        u8 readHeader[4];
        nuPiReadRom(0, readHeader, sizeof(readHeader));
        if (readHeader[0] == 0x80 && readHeader[1] == 0x37 &&
            readHeader[2] == 0x12 && readHeader[3] == 0x40) {
            printf("nuPiReadRom: OK\n");
        } else {
            printf("nuPiReadRom: FAILED\n");
        }
        printf("baserom.z64: OK (%lu bytes)\n", (unsigned long)gGameRomSize);
    } else {
        printf("ROM missing or invalid.\n");
        printf("Copy your US .z64 to:\n");
        printf("sdmc:/3ds/papermario/baserom.z64\n");
    }

    while (aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            break;
        }
    }

    if (gGameRom != NULL) {
        fclose(gGameRom);
    }
    gfxExit();
    return 0;
}
