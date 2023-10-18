#pragma once

#include "../Components/Component.h"
#include "../Utilities/Color.h"

class PointLight : public IComponent
{
public:
	glm::vec4 color = Color::White;
	float intensity = 1.0f;
};

