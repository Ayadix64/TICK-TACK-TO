#ifndef TICK_VERTAX_ARRAY
#define TICK_VERTAX_ARRAY

#include "utils.h"
#include <vector>
struct VectorArrayElement {
	unsigned int type;
	unsigned int count;
	unsigned int normilized;
};



class VertexArray{
private:
	unsigned int m_vaoID=0;
	std::vector<VectorArrayElement>	m_elements;
	unsigned int m_stride=0;
	unsigned int lay=0;

	void NOIN();
private:
	void generite(unsigned int vaaindex, unsigned int type, unsigned int normalized, unsigned int stride,unsigned int count);
	void EnableVAA(unsigned int vaa);
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void Layout();
public:
	template<typename T>
	void AddElement(unsigned int cont){
		loge("VertaxArray ERORR","not sepurted type");
	}
	template<>
	void AddElement<float>(unsigned int cont){
		m_elements.push_back({GL_FLOAT,cont,GL_FALSE});
		m_stride += sizeof(float);
	}
	template<>
	void AddElement<unsigned int>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_INT,cont,GL_FALSE});
		m_stride += sizeof(unsigned int);
	}
	template<>
	void AddElement<unsigned short>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_SHORT,cont,GL_FALSE});
		m_stride += sizeof(unsigned short);
	}
	template<>
	void AddElement<unsigned char>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_BYTE,cont,GL_FALSE});
		m_stride += sizeof(unsigned char);
	}
	template<>
	void AddElement<int>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_INT,cont,GL_FALSE});
		m_stride += sizeof(int);
	}
	template<>
	void AddElement<short>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_SHORT,cont,GL_FALSE});
		m_stride += sizeof(short);
	}
	template<>
	void AddElement<char>(unsigned int cont){
		m_elements.push_back({GL_UNSIGNED_BYTE,cont,GL_FALSE});
		m_stride += sizeof(char);
	}
};

unsigned int SizeOfType(unsigned int type);
#endif
