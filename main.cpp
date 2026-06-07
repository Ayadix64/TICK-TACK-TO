#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "basics.hpp"
#include "utils.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.hpp"
#include "batch.hpp"
#include "shaders.hpp"
#include "basics.hpp"

#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"
void Rotate(double& x,double& y,double xx,double yy,double theta);
void Rotate(double& x,double& y,double&z,double xx,double yy,double zz,double theta,double theta2);

void Rotate(float& x,float& y,double xx,float yy,float theta);
void Rotate(float& x,float& y,float&z,float xx,float yy,float zz,float theta,float theta2);


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


int main(){
	/****************************Init*************************/
	if(!glfwInit()){
		Eloge("GLFW not init");
		return 1;
	}
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = CreatWindow("window", 800, 800);
	
	GlewInit();	
	


	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ImGuiInit(window);
	TickInit();	
	/**********************************************************/
	
	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);
	

	//int shader = CreatShader(g_2DShape_vertexshader, g_2DShape_fragmentshader);	
	//glUseProgram(shader);
	float x=0.0,y=0.0,z=1.0f , r=2.0f, r2=0.0f;

	float yp1=(float)ph/2.0,yp2=(float)ph/2.0f;
	float segments = 1.0;
	glm::mat4 proj; 
	glm::mat4 trans= glm::translate(glm::mat4(1.0), {0.0,0.0,1.0});
	glm::mat4 mv;

	while(!glfwWindowShouldClose(window) ){
			ImGuiNewFrame();
		
		ImGui::Begin("Hello TICK-TACK-TO");
		
		ImGui::Text("Hi, he , hallo, hi");
		ImGui::SliderFloat("z", &z, 0.0f, 10.0f);
		ImGui::SliderFloat("r1", &r, 0.0f, 360.0f);
		ImGui::SliderFloat("steps", &segments, 1, 100);
		ImGui::End();
		
		ImGui::Render();
		
		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			x+=0.05;
		}
		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			x-=0.05;
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			y+=0.05;
			if(yp1>0.0){
				yp1-=5.0;
			}
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
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
			
		DrawLine({0.0f,0.0f}, {200.0f,100.0f}, 20.0,{0,0,255,255});
		DrawRectangel((float)pw-20.0, yp1, 10.0f+r, 50.0f+r, {255,0,0,255});
		DrawRectangel(0.0f, 0.0f, 100.0f, 100.0f, {255,0,0,255});
		DrawCercel((float)pw/2.0, (float)ph/2, r, 1, {0,255,0,255});
	


		
		TickRendre(window);
		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		

		glClear(GL_COLOR_BUFFER_BIT);

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
