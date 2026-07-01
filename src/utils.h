#ifndef UTILS_TICKTACKTO
#define UTILS_TICKTACKTO

#include <complex>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <fstream>
//#ifndef GLAD_GL_IMPLEMENTATION 
//	#define GLAD_GL_IMPLEMENTATION
//	#include <glad/gl.h>
//#endif

#include <GL/glew.h>
#include <GL/gl.h>

#include <GLFW/glfw3.h>

//#define TEXTURES_MAX_SLOT 32


#define DEBUG_MODE //if you want to dosnt enter debug mod and save memory , comment this


typedef unsigned char  u8 ;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

typedef struct{
	float x,y;
} Vec2f;
typedef struct{
	u32 x,y;
}Vec2i;
typedef struct{
	float x,y,z;
} Vec3f;
typedef struct{
	u32 x,y,z;
}Vec3i;
typedef struct{
	float x,y,z,w;
} Vec4f;
typedef struct{
	u32 x,y,z,w;
}Vec4i;
typedef struct{
	u8 r,g,b,a;
}Vec4c;


typedef struct {float x , y; u32 c;} VertexShape;
//bool operator!=(VertexShape v1,VertexShape v){return true;};





#ifdef DEBUG_MODE
#define CHECK_GL_ERORR(x)\
	while(glGetError());\
	(x);\
	while(GLenum err = glGetError()){\
		fprintf(stderr,"[OpenGL ERORR] %s => %x @ \"%s\" ,line %d\n",#x,err,__FILE__,__LINE__);\
	}
#endif

#ifndef DEBUG_MODE
#define CHECK_GL_ERORR(x) (x)
#endif


void loge(std::string lg , std::string ms = "");
void Eloge(std::string ms);
void Wloge(std::string ms);
void readFile(std::string path, std::string& data);
	


#endif 
