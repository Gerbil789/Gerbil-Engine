#include "RatController.h"

RatController::RatController(float _speed)
{
	speed = _speed;
	SetTarget();
}

void RatController::Update()
{
	float distance = glm::length(transform->GetPosition() - target);
	if (distance < 1.0f) {
		SetTarget();
	}
	else {
		transform->MoveBy(dir * speed);
	}
}

void RatController::SetTarget()
{
	target = glm::vec3(std::rand() / static_cast<float>(RAND_MAX) * 10.0f, 0.0f, std::rand() / static_cast<float>(RAND_MAX) * 10.0f);
	dir = glm::normalize(target - transform->GetPosition());
}
 