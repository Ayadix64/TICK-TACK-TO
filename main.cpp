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
	

	GLFWwindow* window = CreatWindow("window", 800, 600);
	GlewInit();	
		

	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ImGuiInit(window);
	/**********************************************************/
	

	BatchRendrer<float> batch(4);
	
	float buffData[]{
		-0.5,-0.5,0.0,0.0,
		 0.5,-0.5,1.0,0.0,
		-0.5,0.5 ,0.0,1.0,
		 0.5,0.5 ,1.0,1.0,
		
	};
	unsigned int indecs[]{
		0,1,2,
		1,2,3,
	};
	

	batch.Push(buffData, sizeof(buffData)/sizeof(float), indecs, sizeof(indecs)/sizeof(unsigned int));


	float buffData2[]{
		-0.5+1.0,  0.5, 0.0,1.0,//0
		 0.5+1.0,  0.5, 1.0,1.0,//1
		-0.5+1.0, -0.5, 0.0,0.0,//2
		 0.5+1.0, -0.5, 1.0,0.0, //3
	};
	unsigned int indecs2[]{
		0,1,2,
		1,2,3
	};
	batch.Push(buffData2, sizeof(buffData2)/sizeof(float), indecs2,sizeof(indecs2)/sizeof(unsigned int));
	
	VertexArray vao;
	vao.Bind();
	
	vao.AddElement<float>(2);
	vao.AddElement<float>(2);

	VertexBuff vb = batch.GetVertrex();
	vb.Bind();	
	vao.Layout();
	
	IndexBuff ib= batch.GetIndex();
	
	unsigned char* buff = (unsigned char*)malloc(640*480*4);	
	for(int i = 0 ; i < 640*480*4 ; i+=4){
		buff[i] = 255;
		buff[i+1] = i%255;
		buff[i+2] = 0;
		buff[i+3] = 255;
	}
	//Texture imagetext(buff,640,480,4);
	free(buff);
	ImageTexture imagetext("p.png");
	imagetext.Binde();
	

	vb.UnBind();
	ib.UnBinde();

	Shader shader("Shaders/vert.shader","Shaders/frag.shader");
	
	float Cube[]{
		 0.3, 0.3,1.0,//0
		 0.3,-0.3,1.0,//1
		-0.3, 0.3,1.0,//2
		-0.3,-0.3,1.0,//3

		 0.3, 0.3,1.5,//4
		 0.3,-0.3,1.5,//5
		-0.3, 0.3,1.5,//6
		-0.3,-0.3,1.5 //7
	};

	u32 CubeIndex[]{
		1,0,2,
		1,2,3,
		
		1,4,0,
		1,5,4,
		
		1,5,7,
		1,7,3,
		
		0,4,6,
		0,2,6,
		
		7,3,6,
		2,3,6,
		
		5,4,7,
		4,6,7
	};
	
	VertexArray cube_vao;
	cube_vao.AddElement<float>(3);
	VertexBuff cube_vb(Cube, sizeof(Cube));
	IndexBuff cube_ib(CubeIndex, sizeof(CubeIndex));
	cube_vb.Bind();
	cube_ib.Bind();
	cube_vao.Layout();
	/*****************************************************************************************************************/
	TickInit();
	
	shader.SetUniform1i("u_Texture",0);
		
	
	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);
	
	
	float clc=0.0;
	
	glm::mat4 proj = glm::ortho(-1.0,1.0,-0.75,0.75,-10.0,10.0);
	glm::mat4 trans = glm::translate(glm::mat4(1.0), {0.0,0.0,1.0});
	float x=-0.5f,y=-0.5f,z=1.0f , r=0.0f, r2=0.0f;
	
	Uniform u_mvp("u_MVP",shader);
	Uniform u_z("u_z",shader);
	while(!glfwWindowShouldClose(window)){
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
			proj=glm::ortho(-1.0f,1.0f,(float)(-(float)h/(float)w),(float)((float)h/(float)w),-10.0f,10.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT);	
		//RnedrerDraw(vao,ib);
	//RnedrerDraw(cube_vao,cube_ib);

		
		DrawRectangel(x, y, 0.3f, 0.3f, {255,0,0,255});

		TickRendre();	
		ImGui::Begin("Hello TICK-TACK-TO");
		ImGui::Text("Hi, he , hallo, hi");
		
		ImGui::SliderFloat("x", &x, -1.0f, 1.0f);
		ImGui::SliderFloat("y", &y, -1.0f, 1.0f);
		ImGui::SliderFloat("z", &z, 0.0f, 10.0f);
		ImGui::SliderFloat("r1", &r, 0.0f, 360.0f);
		ImGui::SliderFloat("r2", &r2, 0.0f, 360.0f);
		

		



		for(int i = 0 ; i < 8*3;i+=3){			
			double x_=Cube[i],y_=Cube[i+1],z_=Cube[i+2];
			Rotate(x_,y_,z_,0.0,0.0,1.15,(double)r,(double)r2);
			Cube[i]=x_,Cube[i+1]=y_,Cube[i+2]=z_;


		}
		cube_vb.reFull(Cube, sizeof(Cube));
			

		//trans = glm::translate(glm::mat4(1.0), {x,y,1.0});
		//trans = glm::rotate(glm::mat4(1.0), z, {0.0,0.0,0.0});
		
		for(int i = 0 ; i < 8 ; i++){
			
		}
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
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			y-=0.05;
		}
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
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
