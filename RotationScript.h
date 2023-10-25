#pragma once

#include "../Components/Component.h"
#include "../Utilities/Time.h"

class RotationScript : public IComponent
{
public:
	RotationScript(float _val = 50.0f, glm::vec3 _dir = glm::vec3(0.0f, 1.0f, 0.0f));
	void Update() override;
private:
	float val;
	glm::vec3 dir;
};

