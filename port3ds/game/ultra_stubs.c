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

