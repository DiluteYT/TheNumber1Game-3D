#include "WindowCreation.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Shapes.h"
#include "Renderer2D.h"

int main()
{

	// WindowCreation should be first 99% of the time.
	WindowCreation wc(glm::vec2(1000, 1000));

	Shader shader("res/shaders/shader.shader");
	shader.Bind();

	Camera camera(glm::perspective(glm::radians(45.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f)); // projection is a common subject for your meshes to not be in the center.
	camera.Bind(shader);

	                  /* Meshes below */
	//-------------------------------------------------------//

	std::vector<Mesh> meshes;

	meshes.emplace_back(Spike_3D(), "res/textures/th.png", shader);
	meshes.emplace_back(Cube(), "res/textures/th.png", shader);

	meshes[0].transform.position = glm::vec3(2, 0, -2);
	meshes[1].transform.position = glm::vec3(-2, 0, -4);

	//-------------------------------------------------------//

	while (!glfwWindowShouldClose(wc.window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Update(shader);

		meshes[0].transform.rotation += glm::vec3(0.01f, 0.01f, 0.01f);
		meshes[1].transform.rotation -= glm::vec3(0.01f, 0.01f, 0.01f);

		for (size_t i = 0; i < meshes.size(); i++)
		{

			if (meshes[i].renderMe)
				meshes[i].Draw();
		}

		glfwSwapBuffers(wc.window); // Dont render anything after swapping the buffers.

		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}