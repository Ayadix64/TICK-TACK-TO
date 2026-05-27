#include "utils.h"
#include "vertexarray.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include "shader.h"

void RnedrerDraw(VertexArray& va, IndexBuff& ib){
	va.Bind();
	ib.Bind();
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	return;
}

void RnedrerDraw(VertexArray& va, IndexBuff& ib,Shader& sh){
	sh.Binde();
	va.Bind();
	ib.Bind();
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	return;
}
