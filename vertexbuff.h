#ifndef TICK_VERTEX_BUFF
#define TICK_VERTEX_BUFF
#include <cassert>
#include "utils.h"
class VertexBuff{
private:
	unsigned int m_renderID=0;
	unsigned int m_size=0;
public:
	VertexBuff(void* buff, unsigned int size);
	~VertexBuff();
	void Bind();
	void UnBind();
	void reFull(void* buff, unsigned int size);
	template<typename T>
	void Set(T var, unsigned int pos){
		assert(pos+sizeof(T)<m_size);
		Bind();
		CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,pos*sizeof(T),sizeof(T),&var));
		return;
	}
	
};

#endif 
