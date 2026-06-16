#ifndef TICK_INDEX_BUFF
#define TICK_INDEX_BUFF
#include "utils.h"
u32 GenIndexBuff(u32* data, u32 size);
void DeletIndexBuff(u32 * indexbuff);
void FullIndexBuff(void* buff, u32 size);
void SetIndexBuff(void* data, u32 size, u32 pos);
void RegenrateIndexBuffer(u32* indexbuff, u32* data, u32 size);

#endif
