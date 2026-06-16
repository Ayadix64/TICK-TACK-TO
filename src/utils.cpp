#include "utils.h"



GLFWwindow* CreatWindow(const char* name, unsigned int width, unsigned int heigth){
	GLFWwindow* window = glfwCreateWindow(width, heigth ,name, NULL, NULL); 
	if(!window){
		Eloge("in window intulsing");
		glfwTerminate();
		quick_exit(0x1);
		return NULL;
	}

	glfwMakeContextCurrent(window);	
	GlewInit();
	glViewport(0, 0, width, heigth);
	return window;
	
}


void GlewInit(){
	const char* runOnWayland = getenv("WAYLAND_DISPLAY");	

	GLenum glewVal = glewInit();
	if(glewVal!=GLEW_OK){
		if(!(glewVal == GLEW_ERROR_NO_GLX_DISPLAY && runOnWayland)){ // a linux guy was her
			Eloge("GLEW not init");
			std::cout << glewGetErrorString(glewVal)<<"\n";
			quick_exit(0x1);

		}
	}
	return;
}
