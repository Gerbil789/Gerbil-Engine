#include "directionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 _color, float _intensity, glm::vec3 _direction) : ILight(_color, _intensity)
{
	componentName = "directionalLight";

	SetDirection(_direction);
}

void DirectionalLight::SetDirection(glm::vec3 _direction)
{
	direction = _direction;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}
