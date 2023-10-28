#pragma once

#include "../Managers/ShaderManager.h"
#include "../Components/Camera.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"
#include "../Managers/SceneManager.h"

class CameraController : public IComponent
{
public:
	CameraController(float _speed = 2.0f, Camera* _cam = nullptr);
	void Update() override;
	void ProcessCameraView();
	float GetSpeed();
	void SetSpeed(float _speed);
	void SetCam(Camera* _cam);
private:
	Camera* cam;
	float speed = 2.0f;

	double lastX = Input::GetMouseX();
	double lastY = Input::GetMouseY();
	double yaw = -90.0f;
	double pitch = 0.0f;
};

