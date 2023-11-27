#pragma once
#include "../Components/Component.h"


class Spline : public IComponent
{
public:
	Spline(const std::vector<glm::vec3>& _controlPoints = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 5.0f, -5.0f), glm::vec3(4.0f, 5.0f, 5.0f), glm::vec3(5.0f, 0.0f, 0.0f) }, bool _closedLoop = false);
	glm::vec3 GetPosition(float t);
	void Draw();

	
private:
	std::vector<glm::vec3> controlPoints;
	bool closedLoop;
	
	float factorial(int n) {
		float result = 1;
		for (int i = 1; i <= n; ++i) {
			result *= i;
		}
		return result;
	}
};

