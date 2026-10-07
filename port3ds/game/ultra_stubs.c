#include "common.h"
#include <stdint.h>

extern u64 plat_ticks(void);

s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    if (mq->validCount >= mq->msgCount) return -1;
    s32 slot = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[slot] = msg;
    mq->validCount++;
    return 0;
}

s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags) {
    if (mq->validCount == 0) return -1; /* blocking needs threads, later */
    if (msg != NULL) *msg = mq->msg[mq->first];
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    return 0;
}

void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 count) {
    mq->mtqueue = NULL;
    mq->fullqueue = NULL;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = count;
    mq->msg = msg;
}

u32 osVirtualToPhysical(void* addr) { return (u32)(uintptr_t)addr; }
u32 osSetIntMask(u32 mask) { return 0; }
u32 osGetCount(void) { return (u32)(plat_ticks() / 6); }
void osWritebackDCache(void* a, s32 n) {}
void osInvalDCache(void* a, s32 n) {}
void osInvalICache(void* a, s32 n) {}
s32 osEPiReadIo(OSPiHandle* h, u32 addr, u32* data) { *data = 0; return 0; }
s32 osEPiWriteIo(OSPiHandle* h, u32 addr, u32 data) { return 0; }
void osCreateThread(OSThread* t, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri) {
    t->priority = pri;
    t->id = id;
}
void osStartThread(OSThread* t) {}
void osSetThreadPri(OSThread* t, OSPri pri) { if (t) t->priority = pri; }
void osStopThread(OSThread* t) {}
OSPiHandle* nuPiCartHandle;

int _Printf(outfun prout, char* arg, const char* fmt, va_list args) {
    /* debug/crash text only: do nothing for now */
    return 0;
}

/* Libultra Math & Matrix Operations */
void guRotateF(float mf[4][4], float a, float x, float y, float z) {
    float sin_val, cos_val;
    float norm;

    if (x == 0.0f && y == 0.0f && z == 0.0f) {
        return;
    }

    norm = 1.0f / sqrtf(x * x + y * y + z * z);
    x *= norm;
    y *= norm;
    z *= norm;

    a *= 3.14159265358979323846f / 180.0f;
    sin_val = sinf(a);
    cos_val = cosf(a);

    mf[0][0] = x * x * (1.0f - cos_val) + cos_val;
    mf[0][1] = y * x * (1.0f - cos_val) + z * sin_val;
    mf[0][2] = z * x * (1.0f - cos_val) - y * sin_val;
    mf[0][3] = 0.0f;

    mf[1][0] = x * y * (1.0f - cos_val) - z * sin_val;
    mf[1][1] = y * y * (1.0f - cos_val) + cos_val;
    mf[1][2] = z * y * (1.0f - cos_val) + x * sin_val;
    mf[1][3] = 0.0f;

    mf[2][0] = x * z * (1.0f - cos_val) + y * sin_val;
    mf[2][1] = y * z * (1.0f - cos_val) - x * sin_val;
    mf[2][2] = z * z * (1.0f - cos_val) + cos_val;
    mf[2][3] = 0.0f;

    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

void guTranslateF(float mf[4][4], float x, float y, float z) {
    mf[0][0] = 1.0f; mf[0][1] = 0.0f; mf[0][2] = 0.0f; mf[0][3] = 0.0f;
    mf[1][0] = 0.0f; mf[1][1] = 1.0f; mf[1][2] = 0.0f; mf[1][3] = 0.0f;
    mf[2][0] = 0.0f; mf[2][1] = 0.0f; mf[2][2] = 1.0f; mf[2][3] = 0.0f;
    mf[3][0] = x;    mf[3][1] = y;    mf[3][2] = z;    mf[3][3] = 1.0f;
}

void guScaleF(float mf[4][4], float x, float y, float z) {
    mf[0][0] = x;    mf[0][1] = 0.0f; mf[0][2] = 0.0f; mf[0][3] = 0.0f;
    mf[1][0] = 0.0f; mf[1][1] = y;    mf[1][2] = 0.0f; mf[1][3] = 0.0f;
    mf[2][0] = 0.0f; mf[2][1] = 0.0f; mf[2][2] = z;    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f; mf[3][1] = 0.0f; mf[3][2] = 0.0f; mf[3][3] = 1.0f;
}

/* N64 ROM layout segment stubs */
u32 charset_letter_content_1_OFFSET = 0;
u32 charset_letter_content_2_OFFSET = 0;
u32 charset_letter_content_3_OFFSET = 0;
u32 charset_letter_content_4_OFFSET = 0;
u32 charset_letter_content_5_OFFSET = 0;
u32 charset_letter_content_6_OFFSET = 0;
u32 charset_letter_content_7_OFFSET = 0;
u32 charset_letter_content_8_OFFSET = 0;
u32 charset_letter_content_9_OFFSET = 0;
u32 charset_letter_content_10_OFFSET = 0;
u32 charset_letter_content_11_OFFSET = 0;
u32 charset_letter_content_12_OFFSET = 0;

u32 charset_letter_content_1_pal_OFFSET = 0;
u32 charset_letter_content_2_pal_OFFSET = 0;
u32 charset_letter_content_3_pal_OFFSET = 0;
u32 charset_letter_content_4_pal_OFFSET = 0;
u32 charset_letter_content_5_pal_OFFSET = 0;
u32 charset_letter_content_6_pal_OFFSET = 0;
u32 charset_letter_content_7_pal_OFFSET = 0;
u32 charset_letter_content_8_pal_OFFSET = 0;
u32 charset_letter_content_9_pal_OFFSET = 0;
u32 charset_letter_content_10_pal_OFFSET = 0;
u32 charset_letter_content_11_pal_OFFSET = 0;
u32 charset_letter_content_12_pal_OFFSET = 0;
