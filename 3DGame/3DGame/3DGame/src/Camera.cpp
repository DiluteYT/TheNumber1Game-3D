#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

void Camera::Bind(Shader& shader) 
{
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("projection", projection);
}

void Camera::Move(const glm::vec2 vector, Shader& shader)
{
	view = glm::translate(view, glm::vec3(-vector.x, -vector.y, 0.0f));
	shader.SetUniformMatrix4fv("view", view);
}
