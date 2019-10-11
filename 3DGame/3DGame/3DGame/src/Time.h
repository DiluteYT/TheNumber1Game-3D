#pragma once

#include "glfw3.h"

class Time {
public:
	float deltaTime = 0;

	void UpdateTime();
private:
	float old_time = glfwGetTime();
	float time = 0;

};
