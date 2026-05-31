#include "utils.h"
#include <cassert>
#include "vertexbuff.h"

VertexBuff::VertexBuff(void* buff, u32 size){
	CHECK_GL_ERORR(glGenBuffers(1,&m_renderID));
	Bind();
	CHECK_GL_ERORR(glBufferData(GL_ARRAY_BUFFER,size,buff,GL_DYNAMIC_DRAW));
	m_size=size;
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

void VertexBuff::reFull(void* buff, u32 sz){
	if(sz>m_size){
		loge("Warning","the send buffer bigger than the original buffur, so it ill be re-generate");
		if(m_renderID){
			CHECK_GL_ERORR(glDeleteBuffers(1,&m_renderID));
		}
		CHECK_GL_ERORR(glGenBuffers(1,&m_renderID));
		Bind();
		CHECK_GL_ERORR(glBufferData(GL_ARRAY_BUFFER,sz,buff,GL_DYNAMIC_DRAW));
		m_size=sz;
		return;
	}	
	Bind();
	CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,0,sz,buff));
	
	return;
}

