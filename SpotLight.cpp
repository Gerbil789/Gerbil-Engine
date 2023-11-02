#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 _color, float _intensity, glm::vec3 _direction) : ILight(_color, _intensity)
{
	componentName = "spotLight";

	direction = _direction;
}

void SpotLight::SetDirection(glm::vec3 _direction)
{
	direction = _direction;
}

glm::vec3 SpotLight::GetDirection()
{
	return direction;
}
