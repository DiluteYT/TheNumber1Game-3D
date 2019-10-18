#pragma once

#include "Renderer2D.h"
#include "Camera.h"
#include "WindowCreation.h" 

class Scene
{
public:
	std::vector<Mesh> Meshes;	

	Camera SceneCamera;

	Scene(WindowCreation& WC, Shader& shader);

	void Update();

};
