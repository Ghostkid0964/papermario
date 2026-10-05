#include <3ds.h>
#include <stdint.h>

/* Ticks at 268.1 MHz (SYSCLOCK_ARM11). */
unsigned long long plat_ticks(void) {
    return svcGetSystemTick();
}

/* Frame timing: call once per frame, returns frames-per-second estimate. */
static unsigned long long last_tick = 0;
static float fps = 0.0f;

float plat_frame(void) {
    unsigned long long now = svcGetSystemTick();
    if (last_tick != 0) {
        float dt = (float)(now - last_tick) / (float)SYSCLOCK_ARM11;
        if (dt > 0.0f) fps = 0.9f * fps + 0.1f * (1.0f / dt);
    }
    last_tick = now;
    return fps;
}
