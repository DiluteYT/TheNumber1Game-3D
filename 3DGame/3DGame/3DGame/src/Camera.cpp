#include "Camera.h"

void Camera::Bind(Shader& shader) 
{
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("projection", projection);
}

void Camera::Update(Shader& shader)
{
	view = glm::mat4(1.0f);

	view = glm::translate(view, -transform.position);
	view = glm::rotate(view, transform.rotation.z, glm::vec3(0, 0, 1));
	view = glm::rotate(view, transform.rotation.y, glm::vec3(0, 1, 0));
	view = glm::rotate(view, transform.rotation.x, glm::vec3(1, 0, 0));

	shader.SetUniformMatrix4fv("view", view);
}
