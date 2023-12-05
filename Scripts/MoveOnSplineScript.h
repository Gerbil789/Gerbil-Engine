#pragma once

#include "../Components/Component.h"
#include "../Components/Spline.h"

class MoveOnSplineScript : public IComponent
{
public:
	MoveOnSplineScript(Spline* _spline);
	void Update() override;
private:
	Spline* spline;
	float t = 0.0f;
	float speed = 0.25f;
};

