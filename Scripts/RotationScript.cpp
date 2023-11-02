#include "RotationScript.h"
#include "../Engine/GameObject.h"

RotationScript::RotationScript(float _val, glm::vec3 _dir)
{
	componentName = "rotationScript";

	val = _val;
	dir = _dir;
}

void RotationScript::Update()
{
	this->transform->RotateBy(val * Time::deltaTime, dir);
}
