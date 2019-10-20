#include "WindowCreation.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Shapes.h"
#include "Renderer2D.h"
#include "Time.h"
#include "Scene.h"

int main()
{

	// WindowCreation should be first 99% of the time.
	WindowCreation wc(glm::vec2(1080, 1080), "3D Game");

	Shader shader("res/shaders/shader.shader");
	shader.Bind();

	Camera camera(glm::perspective(glm::radians(90.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f), shader); // projection is a common subject for your meshes to not be in the center.

	Camera camera2(glm::perspective(glm::radians(90.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f), shader); // projection is a common subject for your meshes to not be in the center.

	Time time;

	                  /* Meshes below */
	//-------------------------------------------------------//

	Mesh CubeMesh(Cube(), "res/textures/th.png",true, shader);
	Mesh Spike_3DMesh(Spike_3D(), "res/textures/dick.png", false, shader);
	Mesh SpikeMesh(Spike(), "res/textures/MyStoneTexture.jpg", false, shader);
	Mesh QuadMesh(Quad(), "res/textures/square.png", false, shader);

	//-------------------------------------------------------//

	int width = 20;
	int length = 20;
	int height = 20;

	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
			for (size_t y = 0; y < height; y++)
			{
				Transform transform;
				transform.position = glm::vec3(x*x,y*y,z*z);
				CubeMesh.NewObject(transform);
			}

		}
	}

	Scene scene1(wc, shader);
	scene1.Meshes.emplace_back(CubeMesh);

	Scene* boundScene = &scene1;

	float movementSpeed = 15.0f;

	double tempx, tempy;
	glm::vec2 m = glm::vec2(0);

	while (!glfwWindowShouldClose(wc.window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time.UpdateTime();

		boundScene->SceneCamera.transform.rotation.x += m.x;
		boundScene->SceneCamera.transform.rotation.y += m.y;

		glfwGetCursorPos(wc.window, &tempx, &tempy);

		if(Input::KeyPressed(83, wc.window))
			boundScene->SceneCamera.transform.position -= (boundScene->SceneCamera.forward * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(87, wc.window))
			boundScene->SceneCamera.transform.position += (boundScene->SceneCamera.forward * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(65, wc.window))
			boundScene->SceneCamera.transform.position -= (boundScene->SceneCamera.right * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(68, wc.window))
			boundScene->SceneCamera.transform.position += (boundScene->SceneCamera.right * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(32, wc.window))
			boundScene->SceneCamera.transform.position.y += movementSpeed * time.deltaTime;
		else if (Input::KeyPressed(340, wc.window))
			boundScene->SceneCamera.transform.position.y -= movementSpeed * time.deltaTime;

		boundScene->Update();

		glfwSwapBuffers(wc.window); // Dont render anything after swapping the buffers.

		boundScene->SceneCamera.CalculateMatrices(shader);
		glfwPollEvents();

		m = Input::UpdateMouse(glm::vec2(tempx, tempy), wc.window);
	}

	glfwTerminate();
	return 0;
}