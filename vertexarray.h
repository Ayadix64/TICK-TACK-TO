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

private:
	void generite(unsigned int vaaindex, unsigned int type, unsigned int normalized, unsigned int stride,unsigned int count , void* offset);
	void EnableVAA(unsigned int vaa);
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void Layout();

	template<typename T>
	void AddElement(unsigned int cont){
		loge("VertexArray Erorr", "UnAllowed type");
	}
	void rebuild();


};

constexpr unsigned int SizeOfType(unsigned int type);


#endif
