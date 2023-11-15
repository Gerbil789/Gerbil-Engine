#pragma once

#include "../Components/Camera.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"

class RatController : public IComponent
{
public:
	RatController(float _speed = 1.0f);
	void Update() override;
private:
	void SetTarget();
	float speed;

	glm::vec3 target;
	glm::vec3 dir;

};

