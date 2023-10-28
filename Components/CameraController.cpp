#include "CameraController.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"

CameraController::CameraController(Camera* _cam)
{
	componentName = "cameraController";

	cam = _cam;
	if (cam == nullptr) {
		std::cerr << "ERROR: CameraController is missing Camera component.\n";
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
}

static double lastX = Input::GetMouseX();
static double lastY = Input::GetMouseY();
static double yaw = -90.0f;
static double pitch = 0.0f;

void CameraController::cursor_callback(GLFWwindow* window, double x, double y)
{
	glm::vec3 direction;

	double xoffset = x - lastX;
	double yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//TO DO: fix this
	SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->SetTarget((glm::normalize(direction)));
}

float CameraController::GetSpeed()
{
	return speed;
}

void CameraController::SetSpeed(float _speed)
{
	speed = _speed;
}
