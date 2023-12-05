#include "Camera.h"
#include "../Engine/Shader.h"

Camera::Camera(float _fov, float _aspect, float _nearPlane, float _farPlane, glm::vec3 _target)
{
	componentName = "camera";

	target = _target;
	fov = _fov;
	aspect = _aspect;
	nearPlane = _nearPlane;
	farPlane = _farPlane;
	projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);

	std::vector<Shader*> shaders = ShaderManager::GetInstance().GetShaderPrograms();
	for (Shader* shader : shaders) {
		Attach(shader);
	}
}

void Camera::SetTarget(glm::vec3 _target)
{
	target = glm::normalize(_target);
	Notify();
}

glm::vec3 Camera::GetLeft()
{
	glm::vec3 up = GetUp();
	glm::vec3 result = glm::cross(up, target);

	if (glm::any(glm::isnan(result))) {
		std::cout << "NaN encountered in cross product: up = " << up.x << " " << up.y << " " << up.z << ", target = " << target.x << " " << target.y << " " << target.z << "\n";
	}

	return glm::normalize(result);
}

glm::vec3 Camera::GetUp()
{
	return glm::vec3(0.0f, 1.0f, 0.0f) * transform->GetRotation();
}

glm::vec3 Camera::GetFront()
{
	return glm::normalize(target);
}

void Camera::SetFov(float _fov)
{
	fov = _fov;
	Notify();
}

void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
	Notify();
}

void Camera::SetNearPlane(float _nearPlane)
{
	nearPlane = _nearPlane;
	Notify();
}

void Camera::SetFarPlane(float _farPlane)
{
	farPlane = _farPlane;
	Notify();
}

float Camera::GetFov()
{
	return fov;
}

float Camera::GetAspect()
{
	return aspect;
}

float Camera::GetNearPlane()
{
	return nearPlane;
}

float Camera::GetFarPlane()
{
	return farPlane;
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}


void Camera::UpdateObserver()
{
	Notify();
}

void Camera::CalculateViewMatrix()
{
	viewMatrix = glm::lookAt(
		transform->GetPosition(),
		transform->GetPosition() + target,
		GetUp()
	);
}

void Camera::CalculateProjectionMatrix()
{
	projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void Camera::Attach(IObserver* _observer)
{
	observers.push_back(_observer);
}

void Camera::Detach(IObserver* _observer)
{
	for (auto it = observers.begin(); it != observers.end(); ++it) {
		if (*it == _observer) {
			observers.erase(it);
			break;
		}
	}
}

void Camera::Notify()
{
	CalculateProjectionMatrix();
	CalculateViewMatrix();

	for (IObserver* observer : observers) {
		observer->UpdateObserver(this);
	}
}

void Camera::SetTransform(Transform* t)
{
	IComponent::SetTransform(t);
	transform->Attach(this);
}
