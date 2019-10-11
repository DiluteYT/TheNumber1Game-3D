#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <vector>

struct Transform
{
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};


struct Vertex {
	glm::vec2 Position;
	glm::vec3 Color;
	glm::vec2 texCoord;
};
class Mesh {
public:
	std::vector<Vertex> Vertices;
	unsigned int VAO;

	Transform transform;

	bool renderMe = true;

	Texture Texture;

	Shader shader;

	// Constructor
	Mesh(const std::vector<Vertex> vertices, const char* texture, const Shader Shader);

	// Draw the mesh
	void Draw();

private:

	unsigned int VBO;

	void setupMesh();


	glm::mat4 to_mat4();

};
