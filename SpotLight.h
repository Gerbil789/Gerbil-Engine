#pragma once
#include "../Components/Light.h"

class SpotLight: public ILight
{
public:
	SpotLight(glm::vec3 _color = Color::White, float _intensity = 1.0f);
};

