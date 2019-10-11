#include "Time.h"

void Time::UpdateTime() {

	time = glfwGetTime();
	deltaTime = time - old_time;
	old_time = time;
}
