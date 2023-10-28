#include "CameraController.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"

CameraController::CameraController(float _speed, Camera* _cam)
{
	componentName = "cameraController";

	speed = _speed;
	
	if (_cam == nullptr) {
		std::cerr << "WARNING: CameraController is missing Camera component.\n";
	}
	else {
		cam = _cam;
	}

}

void CameraController::Update()
{
	if (Input::IsKeyDown(GLFW_KEY_W)) {
		transform->MoveBy(cam->GetFront() * speed * (float)Time::deltaTime);
	}

	if (Input::IsKeyDown(GLFW_KEY_S)) {
		transform->MoveBy(-cam->GetFront() * speed * (float)Time::deltaTime);
	}

	if (Input::IsKeyDown(GLFW_KEY_A)) {
		transform->MoveBy(cam->GetLeft() * speed * (float)Time::deltaTime);
	}

	if (Input::IsKeyDown(GLFW_KEY_D)) {
		transform->MoveBy(-cam->GetLeft() * speed * (float)Time::deltaTime);
	}

	if (Input::IsKeyDown(GLFW_KEY_SPACE)) {
		transform->MoveBy(glm::vec3(0.0f, 1.0f, 0.0f) * speed * (float)Time::deltaTime);
	}

	if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		transform->MoveBy(glm::vec3(0.0f, -1.0f, 0.0f) * speed * (float)Time::deltaTime);
	}

	if (Input::CursorMoved()) {
		ProcessCameraView();
	}
}



void CameraController::ProcessCameraView()
{
	glm::vec3 direction;

	double xoffset = Input::GetMouseX() - lastX;
	double yoffset = lastY - Input::GetMouseY();
	lastX = Input::GetMouseX();
	lastY = Input::GetMouseY();

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	direction.y = static_cast<float>(sin(glm::radians(pitch)));
	direction.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

	cam->SetTarget((glm::normalize(direction)));
}

float CameraController::GetSpeed()
{
	return speed;
}

void CameraController::SetSpeed(float _speed)
{
	speed = _speed;
}

void CameraController::SetCam(Camera* _cam)
{
	cam = _cam;
}
