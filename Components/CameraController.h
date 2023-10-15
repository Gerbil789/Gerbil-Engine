#pragma once

#include "../Managers/ShaderManager.h"
#include "../Components/Camera.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"

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

