#pragma once
#include "../Components/Light.h"

class PointLight : public ILight
{
public:
	PointLight(glm::vec3 _color = Color::White, float _intensity = 1.0f);
};

