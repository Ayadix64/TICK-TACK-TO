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
#include "rendrer.hpp"
#include "basics.cpp"

#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"
void Rotate(double& x,double& y,double xx,double yy,double theta);
void Rotate(double& x,double& y,double&z,double xx,double yy,double zz,double theta,double theta2);

void Rotate(float& x,float& y,double xx,float yy,float theta);
void Rotate(float& x,float& y,float&z,float xx,float yy,float zz,float theta,float theta2);





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
	
	/**********************************************************/
	

	Shader shader("Shaders/vert.shader","Shaders/frag.shader");
	/*****************************************************************************************************************/
	TickInit();
	
	shader.SetUniform1i("u_Texture",0);
		
	
	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);
	
	
	float clc=0.0;
	
	glm::mat4 proj = glm::ortho(0.0f,(float)pw,(float)ph,0.0f,-10.0f,10.0f);
	glm::mat4 trans = glm::translate(glm::mat4(1.0), {0.0,0.0,1.0});
	float x=-0.5f,y=-0.5f,z=1.0f , r=2.0f, r2=0.0f;

	Uniform u_mvp("u_MVP",shader);
	Uniform u_z("u_z",shader);
	
	char ticktackto[3][3];

	float bx =0.0f , by=10.0f;
	float bxa=2.0f,bya=2.0f;
	float yp1=(float)ph/2.0,yp2=(float)ph/2.0f;
	while(!glfwWindowShouldClose(window) ){
		glm::mat4 model = trans*proj;
		u_mvp.SetMat4f(model);
		u_z.Set1f(z);
		
		ImGuiNewFrame();
		
		int w , h;
		glfwGetFramebufferSize(window, &w, &h);
		if(w!=pw || h!=ph){
			glViewport(0, 0, w,h);
			pw=w;
			ph=h;
			proj=glm::ortho(0.0f,(float)w,(float)h,0.0f,-10.0f,10.0f);
		}

		
		DrawRectangel((float)pw-20.0, yp1, 10.0f, 50.0f, {255,0,0,255});
		DrawRectangel(10.0, yp2, 10.0f, 50.0f, {0,0,255,255});

		DrawRectangel(bx, by, 20.0f, 20.0f, {0xff,0xff,0xff,0xff});
		if(by-20>=yp1 && by<=yp1+50.0 && bx+20.0>=pw-20.0 && bx+20.0<=pw-10.0){
			bxa=-bxa;
		}
		bx+=bxa;
		by+=bya;
		
		if(bx+20.0f >= pw || bx<=0.0){
			bxa=-bxa;
		}
		if(by+20.0f >= ph || by<=0.0){
			bya=-bya;
		}
		ImGui::Begin("Hello TICK-TACK-TO");
		
		ImGui::Text("Hi, he , hallo, hi");
		
		//ImGui::SliderFloat("x", &x, -1.0f, 1.0f);
		//ImGui::SliderFloat("y", &y, -1.0f, 1.0f);
		ImGui::SliderFloat("z", &z, 0.0f, 10.0f);
		ImGui::SliderFloat("r1", &r, 0.0f, 360.0f);
		//ImGui::SliderFloat("r2", &r2, 0.0f, 360.0f);
		DrawCercel((float)pw/2.0, (float)ph/2, r, 1, {0,255,0,255});
		DrawTriangle({55.0,55.0}, {55.0,0.0}, {0.0,55.0}, {255,255,0,255});
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
		TickRendre();	
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		

		glClear(GL_COLOR_BUFFER_BIT);
		clc+=0.01;

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
