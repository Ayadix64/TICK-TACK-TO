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
	std::vector<u32> m_Index;
	u32 m_steps = 0;//the cont of elements betwen evry vertex
	u32 m_IndexPtr =0, m_VertexPtr=0;
	bool m_VertexChanged=false;
	bool m_IndexChanged=false;
private:
	void PushIndex(u32 index);
	void PushVertex(T& vert);

public:
	BatchRendrer(u32 steps);
	~BatchRendrer();
	void Push(T* vertex, u32 countofVertex, u32* index, u32 countofIndex);
	void Push(T* vertex, u32 countofVertex, u32& VertexOffset, u32* index, u32 countofIndex,u32& IndexOffset);

	VertexBuff GetVertrex();
	IndexBuff GetIndex();
	void resetPointers();
	u32 getVertexUsedMemory();//to make the api knows when it want to freeup lelory and is it worth it.
	u32 getIndexUsedMemory();
	void FreeUpVertexMemory();
	void FreeUpIndexMemory();
	bool isIndexChanged();
	bool isVertexChanged();
	T* GetVertexData(u32& count);
	u32* GetIndexData(u32& count);


};

#endif
