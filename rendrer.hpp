#ifndef TICK_RENDRER
#define TICK_RENDRER

#include "utils.h"
#include "vertexarray.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include "shader.h"

void RnedrerDraw(VertexArray& va, IndexBuff& ib);

void RnedrerDraw(VertexArray& va, IndexBuff& ib,Shader& sh);

#endif
