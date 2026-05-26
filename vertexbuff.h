#ifndef TICK_VERTEX_BUFF
#define TICK_VERTEX_BUFF
#include <cassert>
#include "utils.h"
class VertexBuff{
private:
	u32 m_renderID=0;
	u32 m_size=0;
public:
	VertexBuff(void* buff, u32 size);
	~VertexBuff();
	void Bind();
	void UnBind();
	void reFull(void* buff, u32 size);
	template<typename T>
	void Set(T var, u32 pos){
		assert(pos+sizeof(T)<m_size);
		Bind();
		CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,pos*sizeof(T),sizeof(T),&var));
		return;
	}
	
};

#endif 
