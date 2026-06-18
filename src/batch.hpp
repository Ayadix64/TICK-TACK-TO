#ifndef TICK_BATCH
#define TICK_BATCH
#include "utils.h"
#include <cassert>
void BatchRendringAddVertex(float** buffer , u32 * bufferSize, u32* pointer, char* isItChanged,float* data, u32 count);
void BatchRendringAddIndex(u32** buffer , u32 * bufferSize, u32* pointer, char* isItChanged,u32* data, u32 count , u32 vertexptr, u32 vertexstrid);

#endif
