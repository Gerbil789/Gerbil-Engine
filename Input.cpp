#include "Input.h"

bool Input::IsKeyPressed(int key) {
	GLFWwindow* window = glfwGetCurrentContext();
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::IsKeyDown(int key) {
	GLFWwindow* window = glfwGetCurrentContext();
	return glfwGetKey(window, key) == GLFW_PRESS && !keyStates[key];
}

bool Input::IsKeyUp(int key) {
	GLFWwindow* window = glfwGetCurrentContext();
	return glfwGetKey(window, key) == GLFW_RELEASE && keyStates[key];
}

bool Input::IsMouseButtonPressed(int button) {
  GLFWwindow* window = glfwGetCurrentContext();
  return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool Input::IsMouseButtonClicked(int button) {
  GLFWwindow* window = glfwGetCurrentContext();
  if (glfwGetMouseButton(window, button) == GLFW_PRESS && !mouseButtonStates[button]) {
    mouseButtonStates[button] = true;
    return true;
  }
  else if (glfwGetMouseButton(window, button) == GLFW_RELEASE) {
    mouseButtonStates[button] = false;
  }
  return false;
}

double Input::GetMouseX() {
  GLFWwindow* window = glfwGetCurrentContext();
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return xpos;
}

double Input::GetMouseY() {
  GLFWwindow* window = glfwGetCurrentContext();
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return ypos;
}

void Input::Update() {
	GLFWwindow* window = glfwGetCurrentContext();
	for (int key = 0; key < GLFW_KEY_LAST; key++) {
		keyStates[key] = glfwGetKey(window, key) == GLFW_PRESS;
	}
}

bool Input::keyStates[GLFW_KEY_LAST] = { false };
bool Input::mouseButtonStates[GLFW_MOUSE_BUTTON_LAST + 1] = { false };