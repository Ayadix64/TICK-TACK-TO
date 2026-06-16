#include "indexbuff.h"
#include "utils.h"
#include "vertexarray.h"

constexpr unsigned int SizeOfType(unsigned int type){
	switch (type) {
		case GL_FLOAT:
			return sizeof(float);
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
		case GL_UNSIGNED_SHORT:
			return sizeof(unsigned short);
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
		case GL_INT:
			return sizeof(int);
		case GL_SHORT:
			return sizeof(short);
		case GL_BYTE:
			return sizeof(char);
		default:
			return 0;

	}
	return 0;

}
u32 GenVertexArray(){
	u32 vao;
	CHECK_GL_ERORR(glGenVertexArrays(1,&vao));
	CHECK_GL_ERORR(glBindVertexArray(vao));
	return vao;
}

void DeletVertexArray(u32* vao){
	CHECK_GL_ERORR(glDeleteVertexArrays(1,vao));
}

void RegenrateVetexArray(u32* vao){
	DeletVertexArray(vao);
	*vao = GenVertexArray();
	return;
}

void GenVAAP(u32 index, u32 type, u32 norm,u32 strid , u32 count , void* offset){
	CHECK_GL_ERORR(glEnableVertexAttribArray(index));
	CHECK_GL_ERORR(glVertexAttribPointer(index,count,type, norm , strid*SizeOfType(type), (void*)offset));

}
