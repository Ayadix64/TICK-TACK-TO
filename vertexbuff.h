#ifndef TICK_VERTEX_BUFF
#define TICK_VERTEX_BUFF
class VertexBuff{
private:
	unsigned int m_renderID=0;
public:
	VertexBuff(void* buff, unsigned int size);
	~VertexBuff();
	void Bind();
	void UnBind();


};

#endif 
