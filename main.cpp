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
#include "utils.h"
#include "vertexbuff.h"
#include "indexbuff.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.hpp"
#include "batch.hpp"

#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"

void RnedrerDraw(VertexArray& va, IndexBuff& ib){
	va.Bind();
	ib.Bind();
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	return;
}

void RnedrerDraw(VertexArray& va, IndexBuff& ib,Shader& sh){
	sh.Binde();
	va.Bind();
	ib.Bind();
	CHECK_GL_ERORR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
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

	shader.SetUniform1i("u_Texture",0);
	
	
	
	
	int pw,ph ;
	glfwGetFramebufferSize(window, &pw, &ph);
	
	
	float clc=0.0;
	
	glm::mat4 proj = glm::ortho(-1.0,1.0,-0.75,0.75,-10.0,10.0);
	glm::mat4 trans = glm::translate(glm::mat4(1.0), {0.0,0.0,1.0});
	float x=-0.5f,y=-0.5f,z=1.0f;
	
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
		RnedrerDraw(vao,ib);
		ImGui::Begin("Hello TICK-TACK-TO");
		ImGui::Text("Hi, he , hallo, hi");
		
		ImGui::SliderFloat("x", &x, -1.0f, 1.0f);
		ImGui::SliderFloat("y", &y, -1.0f, 1.0f);
		ImGui::SliderFloat("z", &z, 0.0f, 10.0f);
		
		vb.Set<float>(x, 0);
		vb.Set<float>(y, 1);
		
		vb.Set<float>(x+1.0, 4);
		vb.Set<float>(y, 5);
		
		vb.Set<float>(x, 8);
		vb.Set<float>(y+1.0, 9);
		
		vb.Set<float>(x+1.0, 12);
		vb.Set<float>(y+1.0, 13);
		
		//trans = glm::translate(glm::mat4(1.0), {x,y,1.0});

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
