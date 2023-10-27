#include "GUI.h"

GUI::GUI(GLFWwindow* _window, Scene* _scene)
{
	scene = _scene;
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

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

	ShowHierarchy();

	ImGui::End();


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShowObject(GameObject* _object) {
	if (_object == nullptr) {
		return;
	}

	bool nodeOpen = ImGui::TreeNode(_object->GetName().c_str());

	if (nodeOpen) {
		for (GameObject* ptr : _object->GetChildren()) {
			ShowObject(ptr);
		}

		ImGui::TreePop();
	}
}

void GUI::ShowHierarchy()
{
	std::vector<GameObject*> objects = scene->GetObjectManager().GetObjects();

	for (GameObject* ptr : objects) {
		if (ptr->GetParent() == nullptr) {
			ShowObject(ptr);
		}
	}
}


void GUI::Dispose()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
