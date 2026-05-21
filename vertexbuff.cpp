#include "utils.h"
#include "vertexbuff.h"

VertexBuff::VertexBuff(void* buff, unsigned int size){
	CHECK_GL_ERORR(glGenBuffers(1,&m_renderID));
	Bind();
	CHECK_GL_ERORR(glBufferData(GL_ARRAY_BUFFER,size,buff,GL_STATIC_DRAW));
	return;
}
VertexBuff::~VertexBuff(){
	if(m_renderID){
		CHECK_GL_ERORR(glDeleteBuffers(1,&m_renderID));
	}else {
		Eloge("No rendrer buffer to delete");
	}
	return;
}

void VertexBuff::Bind(){
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,m_renderID));
	return;
}

void VertexBuff::UnBind(){
	CHECK_GL_ERORR(glBindBuffer(GL_ARRAY_BUFFER,0));
	return;
}
