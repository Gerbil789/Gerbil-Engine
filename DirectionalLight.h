#pragma once
#include "../Components/Light.h"

class DirectionalLight : public ILight
{
public:
	DirectionalLight(glm::vec3 _color = Color::White, float _intensity = 1.0f, glm::vec3 _direction = glm::vec3(0.0f, -1.0f, 0.0f));
	void SetDirection(glm::vec3 _direction);
	glm::vec3 GetDirection();
private:
	glm::vec3 direction;
};

