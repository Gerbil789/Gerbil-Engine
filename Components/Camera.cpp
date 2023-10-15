#include "Camera.h"

Camera::Camera(glm::vec3 _target, float _fov, float _aspect, float _nearPlane, float _farPlane)
{
	target = _target;
	fov = _fov;
	aspect = _aspect;
	nearPlane = _nearPlane;
	farPlane = _farPlane;
}

void Camera::SetTarget(glm::vec3 _target)
{
	target = glm::normalize(_target);
}

glm::vec3 Camera::GetLeft()
{
	return glm::normalize(glm::cross(GetUp(), target));
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
}

void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
}

void Camera::SetNearPlane(float _nearPlane)
{
	nearPlane = _nearPlane;
}

void Camera::SetFarPlane(float _farPlane)
{
	farPlane = _farPlane;
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(
		transform->GetPosition(),
		transform->GetPosition() + target,
		GetUp()
	);
}

glm::mat4 Camera::CalculateProjectionMatrix()
{
	return glm::perspective(fov, aspect, nearPlane, farPlane);
}
