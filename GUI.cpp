#include "GUI.h"

GUI::GUI(GLFWwindow* _window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

}

void GUI::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Always);
	ImGui::Begin("Hiearchy");

	ImGui::Text("This is some useful text.");
	ShowHierarchy(6);

	ImGui::End();


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::ShowHierarchy(int n)
{
	if (n == 0) {
		return;
	}

	// Display a TreeNode for the current level
	bool nodeIsOpen = ImGui::TreeNode("TEST");

	if (nodeIsOpen) {
		// You can add content specific to this hierarchy level here.

		// Recursively call ShowHierarchy with n-1 for children
		ShowHierarchy(n - 1);

		ImGui::TreePop();
	}
}


void GUI::Dispose()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
