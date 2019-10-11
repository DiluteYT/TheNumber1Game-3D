#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include "Shader.h"

struct ctransform {
	glm::vec3 position = glm::vec3(0, 0, 5);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
};

class Camera
{
public:

	glm::vec3 right = glm::vec3(0);
	glm::vec3 up = glm::vec3(0);
	glm::vec3 forward = glm::vec3(0);

	ctransform transform;

	Camera(glm::mat4 c_proj)
		: projection(c_proj) { 
	
	}
	glm::mat4 projection;
	glm::mat4 view = glm::mat4(1.0f);

	void Bind(Shader& shader);
	glm::mat4 transform_to_mat4();
	void CalculateMatrices(Shader& shader);

};
