#pragma once

#include "../Managers/ShaderManager.h"
#include "../Components/Camera.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"
#include "../Managers/SceneManager.h"

class CameraController : public IComponent
{
public:
	CameraController(Camera* _cam);
	void Update() override;
	static void cursor_callback(GLFWwindow* window, double x, double y);
	float GetSpeed();
	void SetSpeed(float _speed);
private:
	Camera* cam;
	float speed = 2.0f;
};

