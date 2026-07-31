#include <stdio.h>


/**
 * helloworld.c
 * this program is a simpel implementation of 
 * */


#ifndef GLAD_GL_IMPLEMENTATION 
	#include "../deps/glad/glad.h"
	#define GLAD_GL_IMPLEMENTATION
#endif

#include "../include/tick-tack-to.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>


int main(){
	if(!glfwInit()){
		return 1;
	}
	
	TickInitWindowFlags();
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	glfwMakeContextCurrent(window);//seting our widow context
	gladLoadGL();//Init our opengl her, this will get all the function adrress of opengl to used;

	
	TickInit(window); //And the


	char FPS[100];
	
	char check=0;
	float slid=0.0;
	double tflf = glfwGetTime();
	

	TextBoxData tbd; //text box data struct; you have to init this 
	InitTextBoxData(&tbd, -1 /*max size, -1 for maximum*/);

	while(!glfwWindowShouldClose(window) ){
		TickNewFrame();//you have to call this in evry frime; or you will have a bed time!

		
		DrawText("Hello World!, World Hello! , whozl[fkgopjg]", 300, 20,(Vec4c){255,255,255,255});
		char butnflags = Button("Hello World\nBoom!", 50, 400,200,0);

		//Button("How is the dat of Kbnuib", 600, 600)
		if(butnflags&1){
			printf("CLICKED!\n");
			fflush(stdout);
		}else if(butnflags&2){
			printf("HOVER\n");
		}
		
		sprintf(FPS, "FPS: %d." , (u32)(1.0/((glfwGetTime()-tflf))));
		DrawText(FPS,0, GetWindowH()-20,(Vec4c){0,255,0,255});

		TextBox( 400, 400,200,0, &tbd);


		CheckBox("Check Box Bora Broa Broa .", 20, 300, (char*)&check);
		
		
		if(check){
			printf("checked , slider : %f \n",slid);
		}
		Slider(200,500,300,&slid);
		//DrawCircle(GetMousePos().x, GetMousePos().y,5, 20, {0,255,0,255})	;

		/******************** Render ********************/
		TickRendre(); /*render our Tick data*/
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clering up our screen
		tflf=glfwGetTime () ;
	}
	
	glfwTerminate();


}
