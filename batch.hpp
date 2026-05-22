#ifndef TICK_BATCH
#define TICK_BATCH
#include "utils.h"
#include "shader.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include <vector>


template<typename T>
class BatchRendrer{
private:
	std::vector<T> m_Vertex;
	std::vector<unsigned int> m_Index;
	unsigned int m_steps = 0;//the cont of elements betwen evry vertex
		

public:
	BatchRendrer(unsigned int steps);
	~BatchRendrer();
	void Push(T* vertex, unsigned int countofVertex, unsigned int* index, unsigned int countofIndex);

	VertexBuff GetVertrex();
	IndexBuff GetIndex();

};

#endif
