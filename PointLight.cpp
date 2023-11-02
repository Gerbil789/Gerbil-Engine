#include "PointLight.h"

PointLight::PointLight(glm::vec3 _color, float _intensity) : ILight(_color, _intensity)
{
	componentName = "pointLight";
}
