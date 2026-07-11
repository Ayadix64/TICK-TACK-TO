<div align="center">
  <h1>TICK-TACK-TO</h1>
  <h3>multipltform OpenGL grahics library</h3>
</div>

*yes i know that i miss prounsed it.*

A fast & minmul proufourmence first UI library build on opengl and C++ for C/C++ applications


## Depdences
- GLFW
- GLEW
- opengl

i realy try to minmize depedences, that is what i came with

## Why?
i dont know, i am not even a ui programing fan,

i think that i allways want a multiplafourm good loking library that is eazy to use, i liked Dear imGui, so i want to make a gui library with the same idea


this library is still in devoloping, so you may meet some litel goohy things, hope you dont,


NOTE: THIS IS NOT A GAME LIBRARY , i never make it for games, not the best chouse



##  Ok, how can i use it?
this library is a glfw library, you have to know how to init a window in glfw and then use it,

```cpp
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "include/tick-tack-to.h"

void GlewInit(){
	const char* runOnWayland = getenv("WAYLAND_DISPLAY");	

	GLenum glewVal = glewInit();
	if(glewVal!=GLEW_OK){
		if(!(glewVal == GLEW_ERROR_NO_GLX_DISPLAY && runOnWayland)){ // a linux guy was her
			fprintf(stderr,"[ERORR] %s\n",glewGetErrorString(glewVal));
            quick_exit(0x1);

		}
	}
	return;
}


int main(){
	/****************************Init*************************/
	if(!glfwInit()){
		fprintf(stderr,"[ERORR] glfw init fail.\n");
        return 1;
	}
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_SAMPLES, 8);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	

	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	glfwMakeContextCurrent(window);
	GlewInit();
	

	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	
	
	TickInit();
	
    while(!glfwWindowShouldClose(window) ){
        DrawText("the fast quick fox jump over the lazy slow dog", 300, 200);
        ReloadTexture(&animatedTextutr, image,300 , 250, 4);
        char butnflags = DrawButton("Butto\nn", x, y);
        if(butnflags&1){
            printf("CLICKED!\n");
            fflush(stdout);
        }else if(butnflags&2){
            printf("HOVER\n");
        }
        DrawRoundedRectangel(x+50, y+50, 100, 100, 30, 90, {0,0,255,255});
        DrawText("BOOM JUMP SCARE", x+70, y+70);
        DrawTextSegment("It wase trome outside, no budy can see the past or the feture ,"
                        "\n bla bla too mush of a talk", 100, 50, 20, 10, 400, 100);	


 

        TickRendre(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}


```


## Fear Allah in your work
## Have a nice day.
