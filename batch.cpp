#include "batch.hpp"
#include "indexbuff.h"
#include "vertexbuff.h"

template <class T>
BatchRendrer<T>::BatchRendrer(unsigned int steps):m_steps(steps){
	m_Vertex.resize(1024);
	m_Index .resize(1024);
}
template <class T>
BatchRendrer<T>::~BatchRendrer(){
	m_Vertex.clear();
	m_Index.clear();
}


template <class T>
void BatchRendrer<T>::PushIndex(unsigned int indec){
	if(m_IndexPtr>=m_Index.size()){
		m_Index.resize(m_Index.size()+1024);
	}
	if(m_Index[m_IndexPtr]!=indec){
		m_IndexChanged=true;
	}
	m_Index[m_IndexPtr]=indec;
	m_IndexPtr++;
	
	return;	
}


template <class T>
void BatchRendrer<T>::PushVertex(T& vert){
	if(m_VertexPtr>=m_Vertex.size()){
		m_Vertex.resize(m_Vertex.size()+1024);
	}
	if(m_Vertex[m_VertexPtr]!=vert){
		m_VertexChanged=true;
	}
	m_Vertex[m_VertexPtr]=vert;
	m_VertexPtr++;
	
	return;	
}






template <class T>
void BatchRendrer<T>::Push(T* vertex, unsigned int countofVertex, unsigned int* index, unsigned int countofIndex){
	for(unsigned int i = 0 ; i < countofIndex; i++){
		PushIndex(index[i]+m_VertexPtr/m_steps);
	}
	for(unsigned int i = 0 ; i < countofVertex; i++){
		PushVertex(vertex[i]);
	}
	return;	
}




template <class T>
void BatchRendrer<T>::Push(T* vertex, unsigned int countofVertex, unsigned int& VertexOffset, unsigned int* index, unsigned int countofIndex,unsigned int& IndexOffset)
{
	IndexOffset=m_IndexPtr;
	for(unsigned int i = 0 ; i < countofIndex; i++){
		PushIndex(index[i]+m_VertexPtr/m_steps);
	}
	
	VertexOffset=m_VertexPtr;
	for(unsigned int i = 0 ; i < countofVertex; i++){
		PushVertex(vertex[i]);
	}
}


template<class T>

VertexBuff BatchRendrer<T>::GetVertrex(){
	
	return VertexBuff(m_Vertex.data(), m_VertexPtr*sizeof(T));
}


template<class T>

IndexBuff BatchRendrer<T>::GetIndex(){
	return IndexBuff(m_Index.data(), m_IndexPtr*sizeof(unsigned int));
}


template<class T>

void BatchRendrer<T>::resetPointers(){
	m_IndexPtr=0;
	m_VertexPtr=0;

	m_IndexChanged=false;
	m_VertexChanged=false;
	return ;
}


template<class T>

unsigned int BatchRendrer<T>::getVertexUsedMemory(){
	return m_Vertex.size()*sizeof(T);
}


template<class T>

unsigned int BatchRendrer<T>::getIndexUsedMemory(){
	return m_Index.size()*sizeof(unsigned int);
}


template<class T>

void BatchRendrer<T>::FreeUpVertexMemory(){
	m_Vertex.clear();
	return ;
}


template<class T>

void  BatchRendrer<T>::FreeUpIndexMemory(){
	m_Index.clear();
	return;
}


template<class T>

bool BatchRendrer<T>::isIndexChanged(){
	return m_IndexChanged;
}

template<class T>

bool BatchRendrer<T>::isVertexChanged(){
	return m_VertexChanged;
}



template class BatchRendrer<float>;
template class BatchRendrer<int>;
template class BatchRendrer<unsigned int>;
