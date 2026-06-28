#include <cstddef>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "include/tick-tack-to.h"
#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"
#include "include/tick-tack-to/basics.h"
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


int main(){
	/****************************Init*************************/
	if(!glfwInit()){
		//Eloge("GLFW not init");
		return 1;
	}
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	glfwMakeContextCurrent(window);
	GlewInit();
	
	// During init, enable debug output
	//glEnable              ( GL_DEBUG_OUTPUT );
	//glDebugMessageCallback( MessageCallback, 0 );

	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	ImGuiIO& io=*ImGuiInit(window);
	TickInit();
	/**********************************************************/
	
	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);
		
	
	//int shader = CreatShader(g_2DShape_vertexshader, g_2DShape_fragmentshader);	
	//glUseProgram(shader);
	float x=0.0,y=0.0,z=1.0f , r=2.0f, r2=0.0f;

	float yp1=(float)ph/2.0,yp2=(float)ph/2.0f;
	float segments = 100.0;
	SetScale(0.5);
	float scale = 1.0f;
	u32 image[320*255]{0xffffffff};
	
	u32 ertheRise = LoadTextureFromeFile("NASA-Apollo8-Dec24-Earthrise.jpg");
	u32 otherertheRise = LoadTextureFromeFile("art002e009287~large.jpg");
	for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((i)&0xff) << 24 | ((i)&0xff) << 16 | ((i)&0xff) << 8 | (i)&0xff;
				image[i*320+ii] = cl;
			}
		}
	u32 animatedTextutr=LoadTexture(image, 320, 200, 4);
	u8 animation=0;
	int adder=1;
	while(!glfwWindowShouldClose(window) ){
		for(int i = 0 ; i < 255 ; i++ ){
			for(int ii = 0 ; ii < 320 ; ii++){
				int cl = ((abs((i+animation)-255/2)*2)&0xff) << 24 | ((abs((i+animation)-255/2)*2)&0xff) << 16 | ((abs((i+animation)-255/2)*2)&0xff) << 8 | (abs((i+animation)-255/2)*2)&0xff;
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
			if(yp1>0.0){
				yp1-=5.0;
			}
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			y+=5.0f;
			if(yp1+50.0<=(float)ph){
				yp1+=5.0;
			}
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
			if(yp2+50.0<=(float)ph){
				yp2+=5.0;
			}
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			if(yp2>0.0){
				yp2-=5.0;
			}
		}
		DrawCircle(x, y,40.0, segments, {0,255,0,255});
	

		DrawTexture(animatedTextutr, 0,0, 200, 200);
		ReloadTexture(animatedTextutr, image, 320, 255, 4);

		glfwMakeContextCurrent(window);
		
		DrawTexture(ertheRise,x, y, 200, 200);
		DrawLine({0.0f,0.0f}, {200.0f,100.0f}, 20.0,{0,0,255,255});
		DrawCircle(200.0f, 100.0f, 10, 20, {0,0,255,255});
		DrawLine({200.0f,100.0f}, {x,y}, 20.0,{0,0,255,255});

		

		TickRendre(window);
		//TickRendre_ctx(window,&window1TickContex);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		//usleep(1000000);
	
	}
	ImGuiStop();
	glfwTerminate();
}





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
