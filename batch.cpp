#include "batch.hpp"
#include "indexbuff.h"
#include "vertexbuff.h"

template <class T>
BatchRendrer<T>::BatchRendrer(unsigned int steps):m_steps(steps){
	m_Vertex.reserve(1024);
	m_Index .reserve(1024);
}
template <class T>
BatchRendrer<T>::~BatchRendrer(){
	m_Vertex.clear();
	m_Index.clear();
}

template <class T>
void BatchRendrer<T>::Push(T* vertex, unsigned int countofVertex, unsigned int* index, unsigned int countofIndex){
	for(unsigned int i = 0 ; i < countofIndex; i++){
		m_Index.push_back(index[i]+m_Vertex.size()/m_steps);
	}
	for(unsigned int i = 0 ; i < countofVertex; i++){
		m_Vertex.push_back(vertex[i]);
	}
	return;	
}

template<class T>

VertexBuff BatchRendrer<T>::GetVertrex(){
	return VertexBuff(m_Vertex.data(), m_Vertex.size()*sizeof(T));
}


template<class T>

IndexBuff BatchRendrer<T>::GetIndex(){
	return IndexBuff(m_Index.data(), m_Index.size()*sizeof(unsigned int));
}

template class BatchRendrer<float>;
template class BatchRendrer<int>;
template class BatchRendrer<unsigned int>;
