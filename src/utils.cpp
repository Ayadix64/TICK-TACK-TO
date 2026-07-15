#include "utils.h"
#include <stdlib.h>
void loge(std::string lg , std::string ms ){
	std::cout << "[" << lg << "] " << ms << ".\n";
	return;
}
void Eloge(std::string ms){
	 std::cerr << "[ERORR] " << ms << ".\n";
}
void Wloge(std::string ms){
	 std::cerr << "[WARNING] " << ms << ".\n";
}

void readFile(std::string path, std::string& data){
	std::ifstream fl(path);
	if(!fl.is_open()){
		Eloge("At opening " + path + " file disnt exiset or curupted");
		return;
	}
	fl.seekg(0,fl.end);
	
	unsigned int u_fileSize = fl.tellg();
	data.resize(u_fileSize);
	
	fl.seekg(0);
	fl.read(data.data(), u_fileSize);
	fl.close();
		
	return;
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






void tRotate(float* x,float* y,float xx,float yy,float theta){
	float raduis=(theta*3.14159)/(180.0);
	float X = *x-xx;
	float Y = *y-yy;
	*x=xx+X*cos(raduis)-Y*sin(raduis);
	*y=yy+X*sin(raduis)+Y*cos(raduis);
	return ;
}

char ReadBitmap(void* bm,u32 num){
	return ((u8*)bm)[num/8]&(1<<(num%8));
}
void SetBitmap(void* bm,u32 num,char val){
	((u8*)bm)[num/8]&=~(1<<(num%8));
	((u8*)bm)[num/8]|=((val&1)<<(num%8));
	return;
}



u32 GetUnicode8Size(char* text,u32 size){
	u32 ret=0;
	for(u32 i = 0 ; i<=size;i++){
		if((((u8)text[i])&(3<<5)) == 1<<6){//10xxxxxxx, a continue
			continue;
		}
		ret++;
	}
	return ret;
}

u32 GetUnicode8(char *text, u32 number,char val){
	u32 unicode=0;
	for(u32 i = 0, uniN=0  ; uniN<=number; i++){
		if(!text[i])return 32;
		if(!(text[i]&(1<<7))){
			unicode=text[i];
			uniN++;
		}else if((text[i]&(3<<6))==1<<7){
			unicode<<=6;
			unicode|=text[i]&0x3f;;	
		}else if ((text[i]&(3<<6))==3<<6 ){
			unicode=0;
			
			uniN++ ;
			int leftshift=6;
			for(int ii = 6 ; ii  >= 0 ;  ii--,leftshift--){
				if(!(text[i]&(1<<ii)))break;
			}
			unicode|=text[i]&~(0xff<<leftshift);
		}
	}
	return unicode;
}


u64 max(u64 v1 , u64 v2){
	return v1>v2?v1:v2;
}
u64 min(u64 v1 , u64 v2){
	return v1>v2?v2:v1;
}
void* PushMatrix(void* val , u32 sizeofstr ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	
	if(usedData+sizeofstr>= dataSize){
		size_t newDataSize = *usedData+sizeofstr+0x1000;
		data=realloc(data,newDataSize);
		
	}
	if(pos>=*dataSize){
		size_t newDataSize = pos+sizeofstr+0x1000;
		data=realloc(data, newDataSize);
		*dataSize=newDataSize;
	}
	for(u32 i = *usedData+sizeofstr; i>pos+sizeofstr; i--){
		((u8*)data)[i-1] = ((u8*)data)[i-sizeofstr-1];
	}
	
	for(u32 i = 0 ; i < sizeofstr ; i++){
		((u8*)data)[i+pos]=((u8*)val)[i];
	}
	*usedData+=sizeofstr;
	return data;
}
void* PushChar   (char val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , 1 , pos,  dataSize , usedData , data);
}
void* PushShort  (short val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , (u32)sizeof(typeof(val)) , pos,  dataSize , usedData , data); //intristing stuff
}
void* PushInteger(int val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , (u32)sizeof(typeof(val)) , pos,  dataSize , usedData , data);
}
void* PushFloat  (float val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , (u32)sizeof(typeof(val)) , pos,  dataSize , usedData , data);
}
void* PushLong   (long val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , (u32)sizeof(typeof(val)) , pos,  dataSize , usedData , data);
}
void* PushDouble (double val  ,size_t pos,  size_t* dataSize , size_t* usedData , void* data){
	return  PushMatrix(&val , (u32)sizeof(typeof(val)) , pos,  dataSize , usedData , data);
}
