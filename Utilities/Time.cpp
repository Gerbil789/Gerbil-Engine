#include "Time.h"


void Time::Update()
{
	float currentTime = static_cast<float>(glfwGetTime());
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

float Time::previousTime = static_cast<float>(glfwGetTime());
float Time::deltaTime = static_cast<float>(glfwGetTime());
