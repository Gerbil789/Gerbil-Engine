#include "Light.h"

Light::Light(int _type, glm::vec3 _color, float _intensity)
{
	type = _type;
	color = _color;
	intensity = _intensity;
}

int Light::GetType()
{
	return type;
}

void Light::SetType(TYPE _type)
{
	type = _type;
}

glm::vec3 Light::GetColor()
{
	return color;
}

void Light::SetColor(glm::vec3 _color)
{
	color = _color;
}

float Light::GetIntensity()
{
	return intensity;
}

void Light::SetIntensity(float _intensity)
{
	intensity = _intensity;
}
