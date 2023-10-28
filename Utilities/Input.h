#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input {
public:
	static bool CursorMoved();

	static bool IsKeyPressed(int key);

	static bool IsKeyDown(int key);

	static bool IsKeyUp(int key);

	static bool IsMouseButtonPressed(int button);

	static bool IsMouseButtonClicked(int button);

	static double GetMouseX();

	static double GetMouseY();

	static void Update();

private:
	static bool keyStates[GLFW_KEY_LAST];
	static bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST + 1];

	static double prevCursorX, prevCursorY;

};