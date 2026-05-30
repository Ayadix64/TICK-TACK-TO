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

VertexArray::VertexArray(){
	CHECK_GL_ERORR(glGenVertexArrays(1,&m_vaoID));
	CHECK_GL_ERORR(glBindVertexArray(m_vaoID));
	return;
}

VertexArray::~VertexArray(){
	CHECK_GL_ERORR(glDeleteVertexArrays(1,&m_vaoID));
	return;
}

void VertexArray::Bind(){
	CHECK_GL_ERORR(glBindVertexArray(m_vaoID));
	return;
}

void VertexArray::UnBind(){
	CHECK_GL_ERORR(glBindVertexArray(0));
	return;
}

void VertexArray::EnableVAA(unsigned int vaa){
	CHECK_GL_ERORR(glEnableVertexAttribArray(vaa));
	return;
}

void VertexArray::generite(unsigned int index, unsigned int type, unsigned int norm , unsigned int stride, unsigned int count, void* offset){
	CHECK_GL_ERORR(glEnableVertexAttribArray(index));
	CHECK_GL_ERORR(glVertexAttribPointer(index,count,type, norm , stride*SizeOfType(type), (void*)offset));
}

void VertexArray::Layout(){
	unsigned int offset=0;

	for(int i = 0 ; i < m_elements.size() ; i++){
		CHECK_GL_ERORR(glEnableVertexAttribArray(i));
		CHECK_GL_ERORR(glVertexAttribPointer(i,m_elements[i].count,m_elements[i].type, m_elements[i].normilized, m_stride , (void*)offset));

		offset+=SizeOfType(m_elements[i].type)*m_elements[i].count;
	}
	return;
}


template<>
void VertexArray::AddElement<float>(unsigned int cont , bool norm){
	m_elements.push_back({GL_FLOAT,cont,norm});
	m_stride += sizeof(float)*cont;
}

template<>
void VertexArray::AddElement<unsigned int>(unsigned int cont , bool norm){
	m_elements.push_back({GL_UNSIGNED_INT,cont,norm});
	m_stride += sizeof(unsigned int)*cont;
}

template<>
void VertexArray::AddElement<unsigned short>(unsigned int cont , bool norm){
	m_elements.push_back({GL_UNSIGNED_SHORT,cont,norm});
	m_stride += sizeof(unsigned short)*cont;
}

template<>
void VertexArray::AddElement<unsigned char>(unsigned int cont , bool norm){
	m_elements.push_back({GL_UNSIGNED_BYTE,cont,norm});
	m_stride += sizeof(unsigned char)*cont;
}

template<>
void VertexArray::AddElement<int>(unsigned int cont , bool norm){
	m_elements.push_back({GL_INT,cont,norm});
	m_stride += sizeof(int)*cont;
}

template<>
void VertexArray::AddElement<short>(unsigned int cont, bool norm){
	m_elements.push_back({GL_SHORT,cont,norm});
	m_stride += sizeof(short)*cont;
}

template<>
void VertexArray::AddElement<char>(unsigned int cont , bool norm){
	m_elements.push_back({GL_BYTE,cont,norm});
	m_stride += sizeof(char)*cont;
}

void VertexArray::rebuild(){
	if(m_vaoID){
		CHECK_GL_ERORR(glDeleteVertexArrays(1,&m_vaoID));
	}
	CHECK_GL_ERORR(glGenVertexArrays(1,&m_vaoID));
	CHECK_GL_ERORR(glBindVertexArray(m_vaoID));
	return;
}
