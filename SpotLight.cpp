#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 _color, float _intensity) : ILight(_color, _intensity)
{
	componentName = "spotLight";
}
