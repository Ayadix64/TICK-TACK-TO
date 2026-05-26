#ifndef TICK_INDEX_BUFF
#define TICK_INDEX_BUFF

#include <cassert>
#include "utils.h"
class IndexBuff{
private:
	u32 m_indexID=0;
	u32 m_count=0;
public:
	IndexBuff(u32 * data, u32 size);
	~IndexBuff();

	void Bind();
	void UnBinde();
	u32 GetCount();

	void reFull(void* buff, u32 size);
	void Set(u32 var, u32 pos){
		assert(pos<m_count);
		Bind();
		CHECK_GL_ERORR(glBufferSubData(GL_ARRAY_BUFFER,pos*sizeof(u32),sizeof(u32),&var));
		return;
	}
};


#endif
