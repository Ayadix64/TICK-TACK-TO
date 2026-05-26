#ifndef UTILS_TICKTACKTO
#define UTILS_TICKTACKTO

#include <complex>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define DEBUG_MODE
typedef unsigned char  u8 ;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

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
