#include "utils.h"

#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"


void  ImGuiInit(GLFWwindow* window){
	ImGui::CreateContext();
	ImGuiIO &io =  ImGui::GetIO();(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return;

}

void  ImGuiNewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
	return;
}

void  ImGuiStop(){
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	return;
}


GLFWwindow* CreatWindow(const char* name, unsigned int width, unsigned int heigth){
	GLFWwindow* window = glfwCreateWindow(width, heigth ,name, NULL, NULL); 
	if(!window){
		Eloge("in window intulsing");
		glfwTerminate();
		quick_exit(0x1);
		return NULL;
	}

	glfwMakeContextCurrent(window);
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
