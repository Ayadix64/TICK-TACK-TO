#ifndef TICK_VERTEX_BUFF
#define TICK_VERTEX_BUFF
#include <cassert>
#include "utils.h"

u32 GenVertexBuffer(void* buff, u32 size);
void FullVertexBuffer(void* buff, u32 size);
void DeletVertexBuffer(u32* vbID);
void SetVertexBuff(void* data, u32 size, u32 pos);
void RegenrateVertexBuffer(u32* vbID, void* buff, u32 size);
#endif 
