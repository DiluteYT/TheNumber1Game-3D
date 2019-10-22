#include "Renderer2D.h"
#include "Time.h"

Mesh::Mesh(std::vector<Vertex> vertices, const char* texture, bool in, bool nn, Shader& thisShader)
	:  Vertices(vertices),
	Mesh_Texture(texture, nn),
	meshShader(thisShader),
	instanced(in)
{
	// create buffers/arrays
	glGenVertexArrays(1, &mesh_VAO);
	glGenBuffers(1, &mesh_VBO);
	glGenBuffers(1, &instanced_mesh_VBO);

	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

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

void Mesh::instancingUpdate()
{
	glBindBuffer(GL_ARRAY_BUFFER, instanced_mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	glBindVertexArray(mesh_VAO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(6, 1);
}


glm::mat4 to_mat4(Transform& transform)
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), transform.position);
	m = glm::rotate(m, transform.rotation.z, glm::vec3(0, 0, 1));
	m = glm::rotate(m, transform.rotation.y, glm::vec3(0, 1, 0));
	m = glm::rotate(m, transform.rotation.x, glm::vec3(1, 0, 0));
	m = glm::scale(m, transform.scale);

	return m;
}

void Mesh::InjectObject(Transform& transform)
{
	modelMatrices.emplace_back(to_mat4(transform));
}
