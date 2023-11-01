#pragma once

#include "../Components/Component.h"
#include "../Utilities/Color.h"

class ILight : public IComponent
{
public:
	ILight(glm::vec3 _color = Color::White, float _intensity = 1.0f);

	glm::vec3 GetColor();
	void SetColor(glm::vec3 _color);

	float GetIntensity();
	void SetIntensity(float _intensity);
	
private:
	glm::vec3 color;
	float intensity;
};

