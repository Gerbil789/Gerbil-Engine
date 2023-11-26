#pragma once

#include "../Components/Component.h"
#include "../Spline.h"

class MoveOnSplineScript : public IComponent
{
public:
	MoveOnSplineScript(Spline* _spline);
	void Move(float t);
private:
	Spline* spline;
};

