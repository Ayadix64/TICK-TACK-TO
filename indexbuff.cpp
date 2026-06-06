#include "utils.h"
#include "indexbuff.h"


u32 GenIndexBuff(u32 *data, u32 size){
	u32 indexbuff;

	CHECK_GL_ERORR(glGenBuffers(1,&indexbuff));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexbuff));
	CHECK_GL_ERORR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_DYNAMIC_DRAW));
	return indexbuff;
}

void DeletIndexBuff(u32 * indexbuff){
	if(*indexbuff){
		CHECK_GL_ERORR(glDeleteBuffers(1,indexbuff));
	}else {
		Eloge("No index buffer to delete");
	}
}
void FullIndexBuff(void* buff, u32 size){
	CHECK_GL_ERORR(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,size,buff));
	return;
}
void SetIndexBuff(void* data, u32 size, u32 pos){
	CHECK_GL_ERORR(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,pos,size,data));
	return;
}


void RegenrateIndexBuffer(u32* indexbuff, u32* data, u32 size){
	DeletIndexBuff(indexbuff);
	*indexbuff = GenIndexBuff(data, size);
	return;
}

