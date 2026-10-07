#include <3ds.h>

typedef struct GameStatus {
    unsigned int curButtons[4];
    unsigned int pressedButtons[4];
    unsigned int heldButtons[4];
    unsigned int prevButtons[4];
    signed char stickX[4];
    signed char stickY[4];
} GameStatus;

extern GameStatus* gGameStatusPtr;

enum Buttons {
    BUTTON_C_RIGHT = 0x00000001,
    BUTTON_C_LEFT  = 0x00000002,
    BUTTON_C_DOWN  = 0x00000004,
    BUTTON_C_UP    = 0x00000008,
    BUTTON_R       = 0x00000010,
    BUTTON_L       = 0x00000020,
    BUTTON_D_RIGHT = 0x00000100,
    BUTTON_D_LEFT  = 0x00000200,
    BUTTON_D_DOWN  = 0x00000400,
    BUTTON_D_UP    = 0x00000800,
    BUTTON_START   = 0x00001000,
    BUTTON_Z       = 0x00002000,
    BUTTON_B       = 0x00004000,
    BUTTON_A       = 0x00008000
};

#define N64_STICK_MAX 80

void update_3ds_inputs(void) {
    hidScanInput();

    u32 kHeld = hidKeysHeld();
    u32 kDown = hidKeysDown();

    circlePosition circle;
    hidCircleRead(&circle);

    u16 currentButtons = 0;
    u16 pressedButtons = 0;

    if (kHeld & KEY_A)      currentButtons |= BUTTON_A;
    if (kHeld & KEY_B)      currentButtons |= BUTTON_B;
    if (kHeld & KEY_START)  currentButtons |= BUTTON_START;
    if (kHeld & KEY_L)      currentButtons |= BUTTON_L;
    if (kHeld & KEY_R)      currentButtons |= BUTTON_R;
    if (kHeld & KEY_ZL)     currentButtons |= BUTTON_Z;
    if (kHeld & KEY_DUP)    currentButtons |= BUTTON_D_UP;
    if (kHeld & KEY_DDOWN)  currentButtons |= BUTTON_D_DOWN;
    if (kHeld & KEY_DLEFT)  currentButtons |= BUTTON_D_LEFT;
    if (kHeld & KEY_DRIGHT) currentButtons |= BUTTON_D_RIGHT;

    if (kHeld & KEY_Y)      currentButtons |= BUTTON_C_LEFT;
    if (kHeld & KEY_X)      currentButtons |= BUTTON_C_UP;

    if (kDown & KEY_A)      pressedButtons |= BUTTON_A;
    if (kDown & KEY_B)      pressedButtons |= BUTTON_B;
    if (kDown & KEY_START)  pressedButtons |= BUTTON_START;

    gGameStatusPtr->curButtons[0] = currentButtons;
    gGameStatusPtr->pressedButtons[0] = pressedButtons;

    s32 stickX = (circle.dx * N64_STICK_MAX) / 156;
    s32 stickY = (circle.dy * N64_STICK_MAX) / 156;

    if (stickX > N64_STICK_MAX)  stickX = N64_STICK_MAX;
    if (stickX < -N64_STICK_MAX) stickX = -N64_STICK_MAX;
    if (stickY > N64_STICK_MAX)  stickY = N64_STICK_MAX;
    if (stickY < -N64_STICK_MAX) stickY = -N64_STICK_MAX;

    gGameStatusPtr->stickX[0] = (s8)stickX;
    gGameStatusPtr->stickY[0] = (s8)stickY;
}

