#include "InternalData.h"
#include "Shader.h"
#include "Scene.h"
#include "WindowCreation.h"
#include "Time.h"
#include "Shapes.h"

int main()
{

	// WindowCreation should be first 99% of the time.
	WindowCreation wc(glm::vec2(1080, 1080), "3D Game");

	Shader shader("res/shaders/shader.shader");
	shader.Bind();

	Time time;

	Scene scene1(&wc, &shader);

	InternalData INTERNAL_DATA(&scene1, &shader, &wc, &time);


	                  /* Meshes below */
	//-------------------------------------------------------//

	Mesh CubeMesh1(Cube(), "res/textures/th.png", true, false, *INTERNAL_DATA.mainShader);
	Mesh CubeMesh2(Spike_3D(), "res/textures/MyStoneTexture.jpg", true, true, *INTERNAL_DATA.mainShader);

	//-------------------------------------------------------//

	unsigned int width = 32;
	unsigned int length = 32;

	Transform transform;
	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
				transform.position = glm::vec3(x * 5, -20, z * 5);
				CubeMesh1.InjectObject(transform);

		}
	}

	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
			transform.position = glm::vec3(x * 3, -19, z * 3);
			CubeMesh2.InjectObject(transform);

		}
	}

	scene1.Meshes.emplace_back(CubeMesh1);
	scene1.Meshes.emplace_back(CubeMesh2);

	float movementSpeed = 50.0f;

	CameraMovement cameramovement(&INTERNAL_DATA, movementSpeed);

	CubeMesh1.instancingUpdate();
	CubeMesh2.instancingUpdate();
	while (!glfwWindowShouldClose(wc.window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		INTERNAL_DATA.SoF_InternalUpdate();

		cameramovement.StartOfFrame();

		glfwSwapBuffers(wc.window); // Dont render anything after swapping the buffers.

		glfwPollEvents();

		INTERNAL_DATA.EoF_InternalUpdate();

		cameramovement.EndOfFrame();

	}

	glfwTerminate();
	return 0;
}