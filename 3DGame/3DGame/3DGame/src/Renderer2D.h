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

glm::mat4 to_mat4(Transform& transform);

class Vertex {
private:
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 texCoord;
public:
	Vertex(glm::vec3 p, glm::vec3 c, glm::vec2 t)
		: Position(p), Color(c), texCoord(t) {}
};

class Mesh {
public:
	std::vector<Vertex> Vertices;
	std::vector<glm::mat4> modelMatrices;

	Texture Mesh_Texture;

	bool instanced = false;
	
	unsigned int mesh_VAO;

	void InjectObject(Transform& transform);

	Shader meshShader;

	void instancingUpdate();
	Mesh(std::vector<Vertex> vertices, const char* texture, bool in, bool nn, Shader& thisShader);
private:

	unsigned int mesh_VBO;
	unsigned int instanced_mesh_VBO;


};