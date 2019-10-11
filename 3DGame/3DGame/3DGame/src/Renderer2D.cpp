#include "Renderer2D.h"

Mesh::Mesh(const std::vector<Vertex> vertices, const char* texture, const Shader Shader)
	: shader(Shader),
	Texture(texture),
	Vertices(vertices)
{
	setupMesh();

}

void Mesh::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture.ID);
	shader.SetUniformMatrix4fv("model", to_mat4());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices.size());

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Mesh::setupMesh()
{


	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glBindVertexArray(VAO);



	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::mat4 Mesh::to_mat4()
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), transform.position);
	m = glm::rotate(m, transform.rotation.z, glm::vec3(0, 0, 1));
	m = glm::rotate(m, transform.rotation.y, glm::vec3(0, 1, 0));
	m = glm::rotate(m, transform.rotation.x, glm::vec3(1, 0, 0));
	m = glm::scale(m, transform.scale);
	return m;
}