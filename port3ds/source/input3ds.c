#include <3ds.h>
#include "common.h"

// N64 controller bitmasks (standard Ultra64)
#define N64_STICK_MAX 80

void update_3ds_inputs(void) {
    hidScanInput();

    u32 kHeld = hidKeysHeld();
    u32 kDown = hidKeysDown();

    circlePosition circle;
    hidCircleRead(&circle);

    // Reset button states
    u16 currentButtons = 0;
    u16 pressedButtons = 0;

    // Button Mapping
    if (kHeld & KEY_A)      currentButtons |= BUTTON_A;
    if (kHeld & KEY_B)      currentButtons |= BUTTON_B;
    if (kHeld & KEY_START)  currentButtons |= BUTTON_START;
    if (kHeld & KEY_L)      currentButtons |= BUTTON_L;
    if (kHeld & KEY_R)      currentButtons |= BUTTON_R;
    if (kHeld & KEY_ZL)     currentButtons |= BUTTON_Z; // Map Z trigger to ZL or L
    if (kHeld & KEY_DUP)    currentButtons |= BUTTON_D_UP;
    if (kHeld & KEY_DDOWN)  currentButtons |= BUTTON_D_DOWN;
    if (kHeld & KEY_DLEFT)  currentButtons |= BUTTON_D_LEFT;
    if (kHeld & KEY_DRIGHT) currentButtons |= BUTTON_D_RIGHT;

    // C-Buttons (mapped to 3DS C-Stick or X/Y buttons)
    if (kHeld & KEY_Y)      currentButtons |= BUTTON_C_LEFT;
    if (kHeld & KEY_X)      currentButtons |= BUTTON_C_UP;

    if (kDown & KEY_A)      pressedButtons |= BUTTON_A;
    if (kDown & KEY_B)      pressedButtons |= BUTTON_B;
    if (kDown & KEY_START)  pressedButtons |= BUTTON_START;

    // Update Paper Mario's active GameStatus struct
    gGameStatusPtr->curButtons[0] = currentButtons;
    gGameStatusPtr->pressedButtons[0] = pressedButtons;

    // Clamp and scale 3DS Circle Pad (-156..156) to N64 range (-80..80)
    s32 stickX = (circle.dx * N64_STICK_MAX) / 156;
    s32 stickY = (circle.dy * N64_STICK_MAX) / 156;

    if (stickX > N64_STICK_MAX)  stickX = N64_STICK_MAX;
    if (stickX < -N64_STICK_MAX) stickX = -N64_STICK_MAX;
    if (stickY > N64_STICK_MAX)  stickY = N64_STICK_MAX;
    if (stickY < -N64_STICK_MAX) stickY = -N64_STICK_MAX;

    gGameStatusPtr->stickX[0] = (s8)stickX;
    gGameStatusPtr->stickY[0] = (s8)stickY;
}
