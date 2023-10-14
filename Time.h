#pragma once
#include <GLFW/glfw3.h>

class Time
{
public:
	static void Update();
	static double deltaTime;

private:
	static double previousTime;

};

