#include "utils.h"
#include <cassert>
#include "vertexbuff.h"
u32 GenVertexBuffer(void* buff, u32 size){
	u32 vb;
	CHECK_GL_ERORR(glGenBuffers(1,&vb));
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,vb));
	CHECK_GL_ERORR(glBufferData(GL_ARRAY_BUFFER,size,buff,GL_DYNAMIC_DRAW));
	return vb;
}
void FullVertexBuffer(void* buff, u32 size){
	CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,0,size,buff));
	return;
}

void SetVertexBuff(void* data, u32 size, u32 pos){
	CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,pos,size,data));

}
void DeletVertexBuffer(u32* vbID){
	if(*vbID){
		CHECK_GL_ERORR(glDeleteBuffers(1,vbID));
	}else {
		Eloge("No vertex buffer to delete");
	}
	return;

}

void RegenrateVertexBuffer(u32* vbID, void* buff, u32 size){
	DeletVertexBuffer(vbID);
	*vbID = GenVertexBuffer(buff, size);
	return;
}
