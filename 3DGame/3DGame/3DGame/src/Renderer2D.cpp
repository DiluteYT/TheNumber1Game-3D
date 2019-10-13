#include "Renderer2D.h"

Mesh::Mesh(const std::vector<Vertex> vertices, const char* texture)
	: Vertices(vertices),
	Mesh_Texture(texture)
{
	setupMesh();
}

Object::Object(Mesh* mesh) 
{
	meshP = mesh;
}

void Object::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, meshP->Mesh_Texture.ID);
	shader.SetUniformMatrix4fv("model", transform.to_mat4());
	glBindVertexArray(meshP->mesh_VAO);
	glDrawArrays(GL_TRIANGLES, 0, meshP->Vertices.size());

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Mesh::setupMesh()
{


	// create buffers/arrays
	glGenVertexArrays(1, &mesh_VAO);
	glGenBuffers(1, &mesh_VBO);

	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glBindVertexArray(mesh_VAO);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::mat4 Transform::to_mat4()
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), position);
	m = glm::rotate(m, rotation.z, glm::vec3(0, 0, 1));
	m = glm::rotate(m, rotation.y, glm::vec3(0, 1, 0));
	m = glm::rotate(m, rotation.x, glm::vec3(1, 0, 0));
	m = glm::scale(m, scale);

	return m;
}