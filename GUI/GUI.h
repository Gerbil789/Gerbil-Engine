#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Engine/Scene.h"
#include "../Utilities/ImageLoader.h"


class GUI
{
public:
	GUI(GLFWwindow* _window, Scene* _scene);
	void Dispose();
	void Update();
private:
	GLuint crosshairTextureID;
	void ShowHierarchy();
	Scene* scene;
	GLFWwindow* window;
};

