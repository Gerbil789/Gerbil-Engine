#pragma once

#include "../Components/Component.h"
#include "../Utilities/Color.h"

class Light : public IComponent
{
public:
	enum TYPE {
		POINT = 1 << 0,			//1
		DIRECTIONAL = 1 << 1,	//2
		SPOTLIGHT = 1 << 2		//4
	};
	Light(int _type = TYPE::POINT, glm::vec3 _color = Color::White, float _intensity = 1.0f);

	int GetType();
	void SetType(TYPE _type);

	glm::vec3 GetColor();
	void SetColor(glm::vec3 _color);

	float GetIntensity();
	void SetIntensity(float _intensity);
	
private:
	int type;
	glm::vec3 color;
	float intensity;
};

