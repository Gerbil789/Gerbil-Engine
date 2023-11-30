#include "GUI.h"

GUI::GUI(GLFWwindow* _window, Scene* _scene)
{
	scene = _scene;
	window = _window;
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	crosshairTextureID = ImageLoader::LoadTexture("Textures/crosshair.png");

}

void GUI::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	int windowWidth, windowHeight;
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	//ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	//ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Always);
	//ImGui::Begin("Scene");
	//ShowHierarchy();
	//ImGui::End();

	ImVec2 windowSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("Crosshair Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
	ImVec2 centerPos = ImVec2((windowWidth - 32) * 0.5f, (windowHeight - 32) * 0.5f); //crosshair texture is 32x32px

	ImGui::SetCursorPos(centerPos);
	ImGui::Image((ImTextureID)(intptr_t)crosshairTextureID, ImVec2(32, 32));

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
