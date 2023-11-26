#pragma once
#include "../Components/Component.h"

class Spline : public IComponent
{
public:
	Spline();
	glm::vec3 GetPosition(float t);
private:
	std::vector<glm::vec3> controlPoints;
};

