#include "utils.h"
#include "indexbuff.h"

IndexBuff::IndexBuff(unsigned int * data, unsigned int count){
	this->m_count = count;
	CHECK_GL_ERORR(glGenBuffers(1,&m_indexID));
	CHECK_GL_ERORR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexID));
	CHECK_GL_ERORR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),data,GL_STATIC_DRAW));
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

unsigned int IndexBuff::GetCount(){
	return this->m_count;
}
