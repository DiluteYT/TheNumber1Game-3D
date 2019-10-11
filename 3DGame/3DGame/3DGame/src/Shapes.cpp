#include "Shapes.h"

std::vector<Vertex> Quad() {

	Vertex vert1;
	vert1.Position = glm::vec2(-100.0f, 100.0f);
	vert1.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert1.texCoord = glm::vec2(0.0f, 1.0f);

	Vertex vert2;
	vert2.Position = glm::vec2(-100.0f, -100.0f);
	vert2.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert2.texCoord = glm::vec2(0.0f, 0.0f);

	Vertex vert3;
	vert3.Position = glm::vec2(100.0f, -100.0f);
	vert3.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert3.texCoord = glm::vec2(1.0f, 0.0f);

	Vertex vert4;
	vert4.Position = glm::vec2(-100.0f, 100.0f);
	vert4.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert4.texCoord = glm::vec2(0.0f, 1.0f);

	Vertex vert5;
	vert5.Position = glm::vec2(100.0f, 100.0f);
	vert5.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert5.texCoord = glm::vec2(1.0f, 1.0f);

	Vertex vert6;
	vert6.Position = glm::vec2(100.0f, -100.0f);
	vert6.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert6.texCoord = glm::vec2(1.0f, 0.0f);


	std::vector<Vertex> placeholder =
	{
		vert1,
		vert2,
		vert3,
		vert4,
		vert5,
		vert6
	};

	return placeholder;

};

std::vector<Vertex> Spike() {

	Vertex vert1;
	vert1.Position = glm::vec2(-100.0f, -100.0f);
	vert1.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert1.texCoord = glm::vec2(0.0f, 0.0f);

	Vertex vert2;
	vert2.Position = glm::vec2(0.0f, 100.0f);
	vert2.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert2.texCoord = glm::vec2(0.5f, 1.0f);

	Vertex vert3;
	vert3.Position = glm::vec2(100.0f, -100.0f);
	vert3.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vert3.texCoord = glm::vec2(1.0f, 0.0f);

	std::vector<Vertex> placeholder =
	{
		vert1,
		vert2,
		vert3
	};

	return placeholder;

};

glm::vec2 DivideBySelf(const glm::vec2& div)
{
	return glm::vec2(div.x / 2, div.y / 2);

}