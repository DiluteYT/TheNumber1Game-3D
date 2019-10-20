#pragma once

#include "Renderer2D.h"
#include "Camera.h"

class WindowCreation;
class CameraMovement;

class Scene
{
public:
	std::vector<Mesh> Meshes;	

	Camera SceneCamera;

	Scene(WindowCreation* WC, Shader* shader);

	void Update();

};
