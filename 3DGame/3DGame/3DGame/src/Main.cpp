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

	Mesh CubeMesh(Cube(), "res/textures/th.png", false, false, *INTERNAL_DATA.mainShader);

	//-------------------------------------------------------//

	unsigned int width = 100;
	unsigned int length = 100;

	for (size_t x = 0; x < width; x++)
	{
		for (size_t z = 0; z < length; z++)
		{
			Transform transform;
			transform.position = glm::vec3(x, -20, z);
			CubeMesh.NewObject(transform);

		}
	}

	scene1.Meshes.emplace_back(CubeMesh);

	float movementSpeed = 15.0f;

	CameraMovement cameramovement(&INTERNAL_DATA, movementSpeed);

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