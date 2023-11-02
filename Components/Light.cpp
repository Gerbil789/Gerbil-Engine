#include "Light.h"

ILight::ILight(glm::vec3 _color, float _intensity)
{
	color = _color;
	intensity = _intensity;
}

glm::vec3 ILight::GetColor()
{
	return color;
}

void ILight::SetColor(glm::vec3 _color)
{
	color = _color;
}

float ILight::GetIntensity()
{
	return intensity;
}

void ILight::SetIntensity(float _intensity)
{
	intensity = _intensity;
}
