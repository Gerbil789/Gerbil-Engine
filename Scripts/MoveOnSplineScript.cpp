#include "MoveOnSplineScript.h"
#include "../Utilities/Time.h"
#include "../Engine/GameObject.h"

MoveOnSplineScript::MoveOnSplineScript(Spline* _spline)
{
	spline = _spline;
}

void MoveOnSplineScript::Update()
{
	if (t >= 1.0f) {
		this->gameObject->Destroy();
		return;
	}


	transform->SetPosition(spline->GetPosition(t) + glm::vec3(0.0f, 0.5f, 0.0f));

	t += Time::deltaTime * speed;
}

