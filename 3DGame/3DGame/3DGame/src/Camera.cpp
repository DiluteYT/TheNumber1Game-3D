#include "Camera.h"

void Camera::Bind(Shader& shader) 
{
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("projection", projection);
}

glm::mat4 Camera::transform_to_mat4()
{
	glm::mat4 m = glm::mat4(1.0f);

	m = glm::translate(view, transform.position);
	m = glm::rotate(view, transform.rotation.z, glm::vec3(0, 0, 1));
	m = glm::rotate(view, transform.rotation.y, glm::vec3(0, 1, 0));
	m = glm::rotate(view, transform.rotation.x, glm::vec3(1, 0, 0));

	return m;

}

void Camera::CalculateMatrices(Shader& shader) {
	glm::mat4 view = glm::inverse(transform_to_mat4());

	right = glm::vec3(view[0]);
	up = glm::vec3(view[1]);
	forward = glm::vec3(view[2]);

	shader.SetUniformMatrix4fv("view", view);
}
