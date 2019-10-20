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

	Mesh Formation_1(Spike_3D(), "res/textures/th.png", true, false, shader);
	Mesh Matrix(Cube(), "res/textures/MyStoneTexture.jpg", true, true, shader);

	//-------------------------------------------------------//

	unsigned int width = 20;
	unsigned int length = 20;
	unsigned int height = 20;

	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
			for (size_t y = 0; y < height; y++)
			{
				Transform transform;
				transform.position = glm::vec3(sqrt(x + y) * 15, sqrt(y + z) * 15, sqrt(z + x) * 15);
				Formation_1.NewObject(transform);
			}

		}
	}

	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
			for (size_t y = 0; y < height; y++)
			{
				Transform transform;
				transform.position = glm::vec3(x * 5, y * 5, z * 5);
				Matrix.NewObject(transform);
			}

		}
	}

	Scene scene1(wc, shader);
	Scene scene2(wc, shader);

	scene1.Meshes.emplace_back(Formation_1);
	scene2.Meshes.emplace_back(Matrix);

	Scene* boundScene = &scene1;

	float movementSpeed = 15.0f;

	double tempx, tempy;
	glm::vec2 m = glm::vec2(0);

	while (!glfwWindowShouldClose(wc.window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Input::KeyPressed(49, wc.window))
		{
			boundScene = &scene1;
		}
		else if (Input::KeyPressed(50, wc.window))
		{
			boundScene = &scene2;
		}

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