#include "Input.h"

bool KeyPressed(int key, GLFWwindow* window)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
		return true;
	else return false;
}