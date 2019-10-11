#include "glew.h"
#include "glfw3.h"
#include "glm/glm.hpp"

class WindowCreation
{
public:


	WindowCreation(glm::vec2 windowsize);
	GLFWwindow* window;

	glm::vec2 windowSize;
	const char *windowName = "2DGame";

};
