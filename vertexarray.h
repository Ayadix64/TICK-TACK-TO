#ifndef TICK_VERTAX_ARRAY
#define TICK_VERTAX_ARRAY
#include "utils.h"
#include <vector>

u32 GenVertexArray();
void DeletVertexArray(u32* vao);
void RegenrateVetexArray(u32* vao);

void GenVAAP(u32 index, u32 type, u32 norm,u32 strid , u32 count , void* offset);

constexpr unsigned int SizeOfType(unsigned int type);


#endif
