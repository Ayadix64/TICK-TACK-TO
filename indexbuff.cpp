#include "utils.h"
#include "indexbuff.h"

IndexBuff::IndexBuff(u32 * data, u32 size){
	this->m_count = size/sizeof(u32);
	CHECK_GL_ERORR(glGenBuffers(1,&m_indexID));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexID));
	CHECK_GL_ERORR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_DYNAMIC_DRAW));
	return;
}

void IndexBuff::Bind(){
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexID));
	return;
}

void IndexBuff::UnBinde(){

	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
	
}

IndexBuff::~IndexBuff(){
	if(m_indexID){
		CHECK_GL_ERORR(glDeleteBuffers(1,&m_indexID));
	}else {
		Eloge("No index buffer to delete");
	}
		
}

u32 IndexBuff::GetCount(){
	return this->m_count;
}


void IndexBuff::reFull(void* buff, u32 sz){
	if(sz>m_count*sizeof(u32)){
		loge("Warning","the send buffer bigger than the original buffur, so it ill be re-generate");
		if(m_indexID){
			CHECK_GL_ERORR(glDeleteBuffers(1,&m_indexID));
		}
		CHECK_GL_ERORR(glGenBuffers(1,&m_indexID));
		Bind();
		CHECK_GL_ERORR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,sz,buff,GL_DYNAMIC_DRAW));
		m_count=sz/sizeof(u32);
		return;
	}
	Bind();
	CHECK_GL_ERORR(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sz,buff));
	return;
}
