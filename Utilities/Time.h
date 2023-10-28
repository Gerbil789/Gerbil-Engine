#pragma once

#include <GLFW/glfw3.h>

class Time
{
public:
	static void Update();
	static float deltaTime;

private:
	static float previousTime;

};

