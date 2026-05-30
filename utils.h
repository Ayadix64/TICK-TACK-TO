#ifndef UTILS_TICKTACKTO
#define UTILS_TICKTACKTO

#include <complex>
#include <cstdlib>
#include <deque>
#include <glm/ext/vector_float4.hpp>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


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


static void loge(std::string lg , std::string ms = ""){
	std::cout << "[" << lg << "] " << ms << ".\n";
	return;
}
static void Eloge(std::string lg){
	loge("ERORR",lg);
}


static void readFile(std::string path, std::string& data){
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


#ifdef DEBUG_MODE
#define CHECK_GL_ERORR(x)\
	while(glGetError());\
	(x);\
	while(GLenum err = glGetError()){\
		std::cout<<"[OpenGL ERROR]"<<" "<<#x <<" --> 0x"<<std::hex << err<< " :: " << std::dec<<__FILE__<<":" <<(int)__LINE__<<"\n";  \
	}
#endif

#ifndef DEBUG_MODE
#define CHECK_GL_ERORR(x) (x)
#endif



void  ImGuiInit(GLFWwindow* window);
void  ImGuiNewFrame();
void  ImGuiStop();

GLFWwindow* CreatWindow(const char* name, unsigned int width, unsigned int heigth);
void GlewInit();


#endif 
