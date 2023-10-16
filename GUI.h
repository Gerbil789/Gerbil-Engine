#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Scene.h"


class GUI
{
public:
	GUI(GLFWwindow* _window, Scene* _scene);
	void Dispose();
	void Update();
private:
	void ShowHierarchy();
	Scene* scene;
};

