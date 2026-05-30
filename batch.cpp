#include "batch.hpp"
#include "indexbuff.h"
#include "utils.h"
#include "vertexbuff.h"
#include <cstring>

template <class T>
BatchRendrer<T>::BatchRendrer(u32 steps):m_steps(steps){
	m_Vertex.resize(1024);
	m_Index .resize(1024);
}


template <class T>
BatchRendrer<T>::BatchRendrer(){
	m_Vertex.resize(1024);
	m_Index .resize(1024);
}

template <class T>
BatchRendrer<T>::~BatchRendrer(){
	m_Vertex.clear();
	m_Index.clear();
}


template <class T>
void BatchRendrer<T>::PushIndex(u32 indec){
	if(m_IndexPtr>=m_Index.size()){
		m_Index.resize(m_Index.size()+1024);
	}
	if(m_Index[m_IndexPtr]!=indec){
		//std::cout<<"\n Was "<<m_Index[m_IndexPtr]<<" and become " << indec <<'\n';
		m_IndexChanged=true;
		m_Index[m_IndexPtr]=indec;
	}

	m_IndexPtr++;
	
	return;	
}


template <class T>
void BatchRendrer<T>::PushVertex(T& vert){
	if(m_VertexPtr>=m_Vertex.size()){
		m_Vertex.resize(m_Vertex.size()+1024);
	}
	if( memcmp(&m_Vertex[m_VertexPtr], &vert, sizeof(T))) {//we actioly some times pass unsigned integers as float, and comparising them is changing them some how, i know that i mess somthing and i will check out it some time, i think that no premenete fix is more than a temprary one, but TODO
		m_VertexChanged=true;
		m_Vertex[m_VertexPtr]=vert;
	}
	m_VertexPtr++;
	
	return;	
}

template <class T>
void BatchRendrer<T>::Push(T* vertex, u32 countofVertex, u32* index, u32 countofIndex){
	for(u32 i = 0 ; i < countofIndex; i++){
		PushIndex(index[i]+m_VertexPtr/m_steps);
	}
	for(u32 i = 0 ; i < countofVertex; i++){
		PushVertex(vertex[i]);
	}
	return;	
}




template <class T>
void BatchRendrer<T>::Push(T* vertex, u32 countofVertex, u32& VertexOffset, u32* index, u32 countofIndex,u32& IndexOffset)
{
	IndexOffset=m_IndexPtr;
	for(u32 i = 0 ; i < countofIndex; i++){
		PushIndex(index[i]+m_VertexPtr/m_steps);
	}
	
	VertexOffset=m_VertexPtr;
	for(u32 i = 0 ; i < countofVertex; i++){
		PushVertex(vertex[i]);
	}
}


template<class T>

VertexBuff BatchRendrer<T>::GetVertrex(){
	
	return VertexBuff(m_Vertex.data(), m_VertexPtr*sizeof(T));
}


template<class T>

IndexBuff BatchRendrer<T>::GetIndex(){
	return IndexBuff(m_Index.data(), m_IndexPtr*sizeof(u32));
}


template <class T>
void BatchRendrer<T>::SetStepsPerVertec(u32 stpes){
	m_steps=stpes;
	return;
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

u32 BatchRendrer<T>::getVertexUsedMemory(){
	return m_Vertex.size()*sizeof(T);
}


template<class T>

u32 BatchRendrer<T>::getIndexUsedMemory(){
	return m_Index.size()*sizeof(u32);
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
template<class T>

T* BatchRendrer<T>::GetVertexData(u32& count){
	count=m_VertexPtr;
	return m_Vertex.data();
}


template<class T>

u32* BatchRendrer<T>::GetIndexData(u32& count){
	count=m_IndexPtr;
	return m_Index.data();
}



template class BatchRendrer<float>;
template class BatchRendrer<int>;
template class BatchRendrer<u32>;
//template class BatchRendrer<VertexShape>;
