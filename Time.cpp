#include "Time.h"


void Time::Update()
{
	double currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

double Time::previousTime = glfwGetTime();
double Time::deltaTime = glfwGetTime();
