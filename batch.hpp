#ifndef TICK_BATCH
#define TICK_BATCH
#include "utils.h"
#include "shader.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include <cassert>
#include <random>
#include <vector>


template<typename T>
class BatchRendrer{
private:
	std::vector<T> m_Vertex;
	std::vector<unsigned int> m_Index;
	unsigned int m_steps = 0;//the cont of elements betwen evry vertex
	unsigned int m_IndexPtr =0, m_VertexPtr=0;
	bool m_VertexChanged=false;
	bool m_IndexChanged=false;
private:
	void PushIndex(unsigned int index);
	void PushVertex(T& vert);

public:
	BatchRendrer(unsigned int steps);
	~BatchRendrer();
	void Push(T* vertex, unsigned int countofVertex, unsigned int* index, unsigned int countofIndex);
	void Push(T* vertex, unsigned int countofVertex, unsigned int& VertexOffset, unsigned int* index, unsigned int countofIndex,unsigned int& IndexOffset);

	VertexBuff GetVertrex();
	IndexBuff GetIndex();
	void resetPointers();
	unsigned int getVertexUsedMemory();//to make the api knows when it want to freeup lelory and is it worth it.
	unsigned int getIndexUsedMemory();
	void FreeUpVertexMemory();
	void FreeUpIndexMemory();
	bool isIndexChanged();
	bool isVertexChanged();
	/*T& operator[](unsigned int n){
		assert(n<m_Vertex.size());
		return &m_Vertex[n];
	}*/

};

#endif
