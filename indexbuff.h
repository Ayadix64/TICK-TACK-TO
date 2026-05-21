#ifndef TICK_INDEX_BUFF
#define TICK_INDEX_BUFF

class IndexBuff{
private:
	unsigned int m_indexID=0;
	unsigned int m_count=0;
public:
	IndexBuff(unsigned int * data, unsigned int count);
	~IndexBuff();

	void Bind();
	void UnBinde();
	unsigned int GetCount();
};


#endif
