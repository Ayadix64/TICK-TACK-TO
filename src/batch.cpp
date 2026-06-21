#include "batch.hpp"
#include "utils.h"
#include <cstdlib>
#include <cstring>



void BatchRendringAddVertex(float** buffer , u32 * bufferSize, u32* pointer, char* isItChanged,float* data, u32 count){
	
	if(!count)return;
	if((*pointer+count)*sizeof(float) > *bufferSize){
		u32 newMemorySize = *bufferSize+count*sizeof(float)+0x1000;
		if(*buffer){
			*buffer=(float*)realloc(*buffer,newMemorySize);

		}else {
			*buffer=(float*)malloc(newMemorySize);
		}
		*bufferSize=newMemorySize;
	}
	for(u32 i = 0 ; i < count ; i++ ){
		if(memcmp(
			&((*buffer)[*pointer+i])
			,&data[i],sizeof(float)
		))
		
		{
			(*buffer)[pointer[0]+i] =data[i];
			*isItChanged=true;
		}
	}
	*pointer+=count;
	return;
}



void BatchRendringAddIndex(u32** buffer , u32 * bufferSize, u32* pointer, char* isItChanged,u32* data, u32 count, u32 vertexPtr, u32 strid){
	if(!count)return;
	if((*pointer+count)*sizeof(float) >= *bufferSize){
		u32 newMemorySize = (*pointer+count)*sizeof(u32)+0x1000;
		if(*buffer){
			*buffer=(u32*)realloc(*buffer,newMemorySize);
		}else {
			*buffer=(u32*)malloc(newMemorySize);
		}
		*bufferSize=newMemorySize;
	}
	for(u32 i = 0 ; i < count ; i++ ){
		u32 data_ = data[i] + (vertexPtr/strid);
		if((*buffer)[*pointer+i]!=data_){
			(*buffer)[*pointer+i]=data_;
			*isItChanged=true;
		}
	}
	*pointer+=count;
	return;
}
