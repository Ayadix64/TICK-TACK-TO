#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
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

void inline ImGuiInit(GLFWwindow* window){
	ImGui::CreateContext();
	ImGuiIO &io =  ImGui::GetIO();(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return;

}

void inline ImGuiNewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
	return;
}

void inline ImGuiStop(){
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	return;
}

int main(){
	if(!glfwInit()){
		Eloge("GLFW not init");
		return 1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	

	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL); 
	if(!window){
		Eloge("in window intulsing");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	const char* runOnWayland = getenv("WAYLAND_DISPLAY");	
	GLenum glewVal = glewInit();
	if(glewVal!=GLEW_OK){
		if(!(glewVal == GLEW_ERROR_NO_GLX_DISPLAY && runOnWayland)){ // a linux guy was her
			Eloge("GLEW not init");
			std::cout << glewGetErrorString(glewVal)<<"\n";
			return 1;

		}
	}
	glm::mat4 proj = glm::ortho(-1.0,1.0,-0.75,0.75,1.0,-1.0);

	glViewport(0, 0, 800, 600);
	std::cout<<"\nOpenGL Version : " << glGetString(GL_VERSION)<<"\n";
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	ImGuiInit(window);
	

	float buffData[]{
		-0.5,  0.5, 0.0,1.0,//0
		 0.5,  0.5, 1.0,1.0,//1
		-0.5, -0.5, 0.0,0.0,//2
		 0.5, -0.5, 1.0,0.0 //3
		
		 //0.0,  0.5,0.0,//4
		 //0.0, -0.5,0.0,//5
		 //0.5,  0.0,0.0,//6
		 //-0.5,  0.0,0.0//7
	};
	unsigned int indecs[]{
		//0,4,7,
		//1,4,6,
		//2,5,7,
		//3,5,6
		0,1,2,
		1,2,3
	};
	
	VertexArray vao;
	vao.Bind();	
	
	vao.AddElement<float>(2);
	vao.AddElement<float>(2);

	VertexBuff vb(buffData,sizeof(buffData));
	
	vao.Layout();
	

	
	IndexBuff ib(indecs,sizeof(indecs)/sizeof(unsigned int));
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
	glm::mat4 trans = glm::translate(glm::mat4(1.0), {0.0,0.0,1.0});
	float x=0.0,y=0.0,z=1.0;
	
	Uniform u_mvp("u_MVP",shader);

	while(!glfwWindowShouldClose(window)){
		glm::mat4 model = proj*trans;
		u_mvp.SetMat4f(model);
		
		ImGuiNewFrame();
		int w , h;
		glfwGetFramebufferSize(window, &w, &h);
		if(w!=pw || h!=ph){
			glViewport(0, 0, w,h);
			pw=w;
			ph=h;
		}

		glClear(GL_COLOR_BUFFER_BIT);
			
		RnedrerDraw(vao,ib);
		ImGui::Begin("Hello TICK-TACK-TO");
		ImGui::Text("Hi, he , hallo, hi");
		
		ImGui::SliderFloat("x", &x, -1.0f, 1.0f);
		ImGui::SliderFloat("y", &y, -1.0f, 1.0f);
		trans = glm::translate(glm::mat4(1.0), {x,y,z});

		ImGui::End();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		clc+=0.01;

	}
	ImGuiStop();
	glfwTerminate();
}
