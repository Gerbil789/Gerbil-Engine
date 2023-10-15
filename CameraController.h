#pragma once
#include "Camera.h"
#include "ShaderManager.h"
#include "Component.h"
#include "Input.h"
#include "Time.h"

class CameraController : public IComponent
{
public:
	CameraController();
	void Update() override;
	static void cursor_callback(GLFWwindow* window, double x, double y);
	float playerSpeed = 2.0f;
private:
	Camera* cam;
};

