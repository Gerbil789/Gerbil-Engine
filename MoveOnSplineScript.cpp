#include "MoveOnSplineScript.h"

MoveOnSplineScript::MoveOnSplineScript(Spline* _spline)
{
	spline = _spline;
}

void MoveOnSplineScript::Move(float t)
{
	this->transform->SetPosition(spline->GetPosition(t));
}
