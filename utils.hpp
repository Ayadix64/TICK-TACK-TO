#include "externel/imgui/imgui.h"
#include "externel/imgui/imgui_impl_glfw.h"
#include "externel/imgui/imgui_impl_opengl3.h"



static ImGuiIO* ImGuiInit(GLFWwindow* window){
	ImGui::CreateContext();
	ImGuiIO &io =  ImGui::GetIO();(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return &io;

}

static void  ImGuiNewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
	return;
}

static void  ImGuiStop(){
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	return;
}
