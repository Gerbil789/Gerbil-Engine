#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Components/Component.h"

class Camera : public IComponent
{
public:
	Camera(
		glm::vec3 _target = glm::vec3(0.0f),
		float _fov = 45.0f,
		float _aspect = 4.0f / 3.0f,
		float _nearPlane = 0.1f,
		float _farPlane = 100.0f
	);

	void SetTarget(glm::vec3 _target);
	glm::vec3 GetLeft();
	glm::vec3 GetUp();
	glm::vec3 GetFront();
	void SetFov(float _fov);
	void SetAspect(float _aspect);
	void SetNearPlane(float _nearPlane);
	void SetFarPlane(float _farPlane);
	glm::mat4 CalculateViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
private:
	glm::vec3 target;
	float fov;
	float aspect;
	float nearPlane;
	float farPlane;
};

