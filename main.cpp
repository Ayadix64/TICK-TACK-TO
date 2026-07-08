#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdlib>
#include "include/tick-tack-to.h"
#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"
#include "include/tick-tack-to/basics.h"
#include "include/tick-tack-to/text.h"
#include "utils.hpp"
#include "src/utils.h"
#include <unistd.h>
void Rotate(double& x,double& y,double xx,double yy,double theta);
void Rotate(double& x,double& y,double&z,double xx,double yy,double zz,double theta,double theta2);

void Rotate(float& x,float& y,double xx,float yy,float theta);
void Rotate(float& x,float& y,float&z,float xx,float yy,float zz,float theta,float theta2);


void GlewInit(){
	const char* runOnWayland = getenv("WAYLAND_DISPLAY");	

	GLenum glewVal = glewInit();
	if(glewVal!=GLEW_OK){
		if(!(glewVal == GLEW_ERROR_NO_GLX_DISPLAY && runOnWayland)){ // a linux guy was her
			//Eloge("GLEW not init");
			std::cout << glewGetErrorString(glewVal)<<"\n";
			quick_exit(0x1);

		}
	}
	return;
}
void GoodOldTesting(){
	u32 cl = 0xff0000ff;
	float veteces[]{
		0.0,100.0,*(float*)&cl,
		100.0,0.0,*(float*)&cl,
		100.0,100.0,*(float*)&cl
	};
	u32 indeces[]{0,1,2};
	u32 vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	u32 vb;
	glGenBuffers(1,&vb);
	glBindBuffer(GL_ARRAY_BUFFER,vb);
	glBufferData(GL_ARRAY_BUFFER,sizeof(veteces),veteces,GL_DYNAMIC_DRAW);
	u32 ib;
	glGenBuffers(1,&ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,3*4,0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,3*4,(void*)8);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vb);
	glDeleteBuffers(1,&ib);
	return;
}
void GoodOldTesting2(float z){
	u32 cl = 0xffff00ff;
	float veteces[]{
		0.0,100.0,z,*(float*)&cl,
		100.0,0.0,z,*(float*)&cl,
		100.0,100.0,z,*(float*)&cl
	};
	u32 indeces[]{0,1,2};
	u32 vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	u32 vb;
	glGenBuffers(1,&vb);
	glBindBuffer(GL_ARRAY_BUFFER,vb);
	glBufferData(GL_ARRAY_BUFFER,sizeof(veteces),veteces,GL_DYNAMIC_DRAW);
	u32 ib;
	glGenBuffers(1,&ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces,GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,4*4,0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,4*4,(void*)12);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vb);
	glDeleteBuffers(1,&ib);
	return;
}


void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}


bool DrawButton(const char* str , float x , float y,GLFWwindow* window){
	u32 w , h;
	GetTextDemensions(str, &w, &h);
	//w+=10;
	//h+=10;
	double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
	bool clicked = false;

	if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		clicked=true;
		printf("CLCD\n");
	}
	if(xpos >= x && xpos<=x+w && 
	   ypos>= y && ypos <= y+h&& !clicked){
		DrawRectangel(x, y, w, h, {100,100,200,255});
	}else if(xpos >= x && xpos<=x+w && 
	   ypos>= y && ypos <= y+h&& clicked){
		DrawRectangel(x, y, w, h, {150,150,250,255});
	}else {
		DrawRectangel(x, y, w, h, {75,75,100,255});
	}
	DrawText(str, x, y);
	return clicked;
}


int main()<%
	/****************************Init*************************/
	if(!glfwInit()){
		//Eloge("GLFW not init");
		return 1;
	}
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	

	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	glfwMakeContextCurrent(window);
	GlewInit();
	
	// During init, enable debug output
	glEnable              ( GL_DEBUG_OUTPUT );
	glDebugMessageCallback( MessageCallback, 0 );

	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	
	ImGuiIO& io=*ImGuiInit(window);
	
	TickInit();
	



	/**********************************************************/





	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);



	float x=0.0,y=0.0,z=1000.0f , r=2.0f, r2=0.0f;
	float segments = 100.0;
	float scale = 1.0f;
	u32 image[320*255]{0xffffffff};
	
	for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((i)&0xff) << 24 | ((i)&0xff) << 16 | ((i)&0xff) << 8 | (i)&0xff;
				image[i*320+ii] = cl;
			}
		}
	
	TickTexture2D otherertheRise = LoadTextureFromeFile("art002e009287~large.jpg");
	TickTexture2D animatedTextutr=LoadTexture(image, 320, 200, 4);
	TickFont fira = LoadFont("FiraCode.ttf", 25, {0,0,255,155});
	
	u8 animation=0;
	int adder=1;
	SetDefaultFont(&fira);
	u64 tflf = clock();
	while(!glfwWindowShouldClose(window) ){
		
		for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((abs((i+animation)-255/2)*2)&0xff) << 24 | 
					 ((abs((i+animation)-255/2)*2)&0xff) << 16 |
					 ((abs((i+animation)-255/2)*2)&0xff) << 8  |
					  (abs((i+animation)-255/2)*2)&0xff;
				image[i*320+ii] = cl;
		 	}
		}
				if(animation==255)adder=-1;
		if(animation==0)adder=1;
		animation+=adder;

		ImGuiNewFrame();
		TickNewFrame();

		ImGui::Begin("Hello TICK-TACK-TO");
		
		ImGui::Text("Hi, he , hallo, hi");
		ImGui::SliderFloat("steps", &segments, 1, 360);
		ImGui::SliderFloat("Scale", &scale , 0.0f,10.0f);
		
		ImGui::Text("latency: %.3f ms/frame\nFPS: %.1f", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
		SetScale(scale);
		ImGui::Render();
		
		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			x+=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			x-=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			y-=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			y+=5.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		}
		if(glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
			printf("CLCD\n");
		}
		
		
		glfwMakeContextCurrent(window);
		

		DrawTexture(animatedTextutr, 0,0, 200, 200);
		DrawLine({0.0f,0.0f}, {200.0f,200.0f}, 20.0,{0,0,255,255});
		
		DrawCircle(200.0f, 200.0f, 10, 20, {0,0,255,255});
		
		DrawLine({200.0f,200.0f}, {x,y}, 20.0,{255,255,255,20});
		
		DrawText("the fast quick fox jump over the lazy slow dog", 300, 200);
		ReloadTexture(&animatedTextutr, image,300 , 250, 4);

		if(DrawButtonPos("Button", x, y)){
			printf("CLICKED!\n");
			fflush(stdout);
		}
		DrawRoundedRectangel(x+50, y+50, 100, 100, 30, 90, {0,0,255,255});
		DrawText("BOOM JUMP SCARE 67", x+70, y+70);
		DrawTextSegment("It wase trome outside, no budy can see the past or the feture , popole are like a cows been threfet evry one on eche ether ther eat.", x, y, animation/4, 0, 400, 100);	
		


		TickRendre(window);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(1);
	}
	ImGuiStop();
	
	glfwTerminate();
%>





void Rotate(double& x,double& y,double xx,double yy,double theta){
	double raduis=(theta*3.14159)/(180.0);
	double X = x-xx;
	double Y = y-yy;
	x=xx+X*cos(raduis)-Y*sin(raduis);
	y=yy+X*sin(raduis)+Y*cos(raduis);
	return ;
}



void Rotate(double& x,double& y,double&z,double xx,double yy,double zz,double theta , double theta2){
	Rotate(x,y,xx,yy,theta);
	Rotate(z,y,zz,yy,theta2);
}






void Rotate(float& x,float& y,float xx,float yy,float theta){
	float raduis=(theta*3.14159)/(180.0);
	float X = x-xx;
	float Y = y-yy;
	x=xx+X*cos(raduis)-Y*sin(raduis);
	y=yy+X*sin(raduis)+Y*cos(raduis);
	return ;
}



void Rotate(float& x,float& y,float&z,float xx,float yy,float zz,float theta , float theta2){
	Rotate(x,z,xx,zz,theta);
	
	Rotate(z,y,zz,yy,theta2);
}
