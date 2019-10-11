#pragma once

#include "glm/glm.hpp"
#include "Shader.h"

class Camera
{
public:

	Camera(glm::mat4 c_proj, glm::mat4 c_view)
		: projection(c_proj),
		view(c_view) { }
	glm::mat4 projection;
	glm::mat4 view;

	void Bind(Shader& shader);
	void Move(const glm::vec2 vector, Shader& shader);

};
