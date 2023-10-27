#include "RotationScript.h"

RotationScript::RotationScript(float _val, glm::vec3 _dir)
{
	val = _val;
	dir = _dir;
}

void RotationScript::Update()
{
	this->transform->RotateBy(val * Time::deltaTime, dir);
}
