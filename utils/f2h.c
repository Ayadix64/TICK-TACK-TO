#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef unsigned int u32;
typedef unsigned long u64;

typedef char bool;
#define false 0
#define true 1

/*
MIT License

Copyright (c) 2026 Chamseddine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

u64 max(u64 v1 , u64 v2){
	return v1>v2?v1:v2;
}
u64 min(u64 v1 , u64 v2){
	return v1>v2?v2:v1;
}
void* Push(char* val , u32 sizeofstr ,u64 pos,  u64* dataSize , u64* usedData , char* data){
	
	if(usedData+sizeofstr>= dataSize){
		u64 newDataSize = *dataSize+max(0x1000,*usedData+sizeofstr);
		char* newdata = (char*)malloc(newDataSize);
		memcpy(newdata, data, *dataSize);
		free(data);
		data=newdata;
		*dataSize=newDataSize; 
	}
	if(pos>=*dataSize){
		u64 newDataSize = *dataSize+max(0x1000,*usedData+sizeofstr);
		char* newdata = (char*)malloc(*dataSize+max(0x1000,pos));
		memcpy(newdata, data, *dataSize);
		free(data);
		data=newdata;
		*dataSize=newDataSize;
	}
	for(u32 i = *usedData+sizeofstr; i>pos+sizeofstr; i--){
		data[i-1] = data[i-sizeofstr-1];
	}
	
	for(u32 i = 0 ; i < sizeofstr ; i++){
		data[i+pos]=val[i];
	}
	*usedData+=sizeofstr;
	return data;
}



unsigned long GetFileSize(FILE* fl){
	if(fl==NULL){
		printf("err in file\n");
		return -1;
	}
	long prev=ftell(fl);
	if(fseek(fl, 0L, SEEK_END)==-1){
		printf("files to fseek");
		return -1;
	}
	unsigned long fileSize = ftell(fl);
	fseek(fl, prev, SEEK_SET);
	return fileSize;

}


void* readFile(const char* fileName , unsigned long * sizeOUT){
	FILE* file = fopen(fileName, "r");
	if(file==NULL){
		printf("err in opening file\n");
		return NULL;
	}
	unsigned long fileSz = GetFileSize(file);
	*sizeOUT=fileSz;
	
	if(fileSz!=-1){
		char* data = (char*)malloc(fileSz);
		fread(data, fileSz, 1, file);
		
		
		fclose(file);
		return data;
	}

	fclose(file);
	return NULL;
}



void WriteConstCharHaderFile(const char* haderName, char* matrixName , char* data , u64 sizeofData ,bool append ){
	FILE* hader = fopen(haderName, append?"a":"w");
	if(!hader){
		printf("Erorr in writing hader file");
		return;
	}
	for(u32 i = 0 ; i < strlen(matrixName); i++){
		switch (matrixName[i]) {
			case '.':
				matrixName[i]='_';
				break;
			case '"':
				matrixName[i]='_';
				break;
			case  '\'':
				matrixName[i]='_';
				break;
			case '@':
				matrixName[i]='/';
				break;
			case '%':
				matrixName[i]='_';
				break;
			default:
				break;
		};
		
	}
	if( matrixName[0] <='9' && matrixName[0] >='0'){
		matrixName[0]='_';
	}
	
	
	if(append){
		fprintf(hader, "\n\n\n/********************************************%s***********************************************/\n",matrixName);
	}
	fprintf(hader, "const char* %s = \n",matrixName);
	fwrite(data, 1, sizeofData-1,hader);
	//fwrite(const void *__restrict ptr, size_t size, size_t n, FILE *__restrict s)
	fprintf(hader, ";");
	fclose(hader);
	return;
}



void WriteMatrixHaderFile(const char* haderName, char* matrixName , char* data , u64 sizeofData,bool append){
	FILE* hader = fopen(haderName, append?"a":"w");
	if(!hader){
		printf("Erorr in writing hader file");
		return;
	}
	for(u32 i = 0 ; i < strlen(matrixName); i++){
		switch (matrixName[i]) {
			case '.':
				matrixName[i]='_';
				break;
			case '"':
				matrixName[i]='_';
				break;
			case  '\'':
				matrixName[i]='_';
				break;
			case '@':
				matrixName[i]='/';
				break;
			case '%':
				matrixName[i]='_';
				break;
			default:
				break;
		};
		
	}
	if( matrixName[0] <='9' && matrixName[0] >='0'){
		matrixName[0]='_';
	}
	
	if(append){
		fprintf(hader, "\n\n\n/********************************************%s***********************************************/\n",matrixName);
	}

	fprintf(hader, "const char %s[]{ \n\t",matrixName);
	
	for(u64 i = 0 ; i < sizeofData ; i++){
		if(!(i%10)){
			fprintf(hader, "\n\t");
		}
		fprintf(hader, "%d , ",(u32)data[i]);
		
	}
	//fwrite(const void *__restrict ptr, size_t size, size_t n, FILE *__restrict s)
	fprintf(hader, "};");
	fclose(hader);
	return;
}




void* Text2String(char* data, u64* dataSize, u64* usedData){
	for(u64 i = *dataSize ; i > 0 ; i--){
		if(data[i-1] == '\n'){
			data = (char*)Push("\t\"", 2, i, dataSize, usedData, data);
			data = (char*)Push("\\n\"", 3, i-1, dataSize, usedData, data);

		}
		if(data[i-1]=='"' ){
			if(i>2 && data[i-2]=='\\' && data[i-3]!='\\'){
				continue;
			}
			data = (char*)Push("\\", 1, i-1, dataSize, usedData, data);
		}
	}
	if(data[*usedData-1]=='"'){
		data[*usedData-1]='\0';
	}

	data=(char*)Push("\t\"", 2, 0, dataSize, usedData, data);
	return  data;
}




int main(int argc, char** arg){
	printf("*** File2.H ***\n");
	if(argc>=2) 
	{	
		u32 arglng = strlen(arg[1]);
		if( (arglng==2 & !memcmp(arg[1], "-h", 2)) || 
		    (arglng==6 & !memcmp(arg[1], "--help", 6))
		  ){
			printf("Welcome to File2.H!\nthis programe is under the MIT License\ncheckout the github repo: https://github.com/chamseddine2009-06/File2.H\n\n");
			printf("===> [arg1 fileName] [arg2 2haderName] [arg3 StringName] -Option1 -Option2 ...\n"
			       "\nOptions:\n"	
			       "\t-m or --matrix if you want to save it as matrix not as a string.\n"
			       "\t-a or --appand if you dont want to over-write the data in the Haderfile.\n");
			return 0;
		}
	}

	if(argc<=3){
		printf("wrong argmentes struct, type -h for help\n");
		return 1;
	}
	bool matrixmode = false;
	bool appendmode = false;
	if(argc>3){
		for(int i = 3 ; i < argc ; i++){
			if(strlen(arg[i])==2 && !memcmp(arg[i] ,"-m", 2)){
				printf("\nYou are in matrix mode, all the data in your file will save a matrix not a string.\n");
				matrixmode = true;
			}
			if(strlen(arg[i])==2 && !memcmp(arg[i] ,"-a", 2)){
				printf("\nYou are in appand mode.\n");
				appendmode = true;
			}
			if(strlen(arg[i])==8 && !memcmp(arg[i] ,"--matrix", 8)){
				printf("\nYou are in matrix mod, all the data in your file will save a matrix not a string.\n");
				matrixmode = true;
			}
			if(strlen(arg[i])==8 && !memcmp(arg[i] ,"--append", 8)){
				printf("\nYou are in appand mode.\n");
				appendmode = true;
			}
		}
	}
		
	u64 dataSize=0;
	char* data = (char*)readFile(arg[1], &dataSize);
	u64 usedData = dataSize;
	printf("file %s size %d \n",arg[1],dataSize);
	if(!matrixmode){
		printf("Data size %d\n" , dataSize);
		data = Text2String(data, &dataSize, &usedData);
		WriteConstCharHaderFile(arg[2],arg[3], data, usedData,appendmode);
	}else {
		WriteMatrixHaderFile(arg[2], arg[3], data, dataSize,appendmode);
	}
	
	return 0;

}
