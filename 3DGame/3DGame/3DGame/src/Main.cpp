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

	Camera camera(glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, 0.0f, 10.0f), glm::mat4(1.0f)); // projection is a common subject for your meshes to not be in the center.
	camera.Bind(shader);

	                  /* Meshes below */
	//-------------------------------------------------------//

	std::vector<Mesh> meshes;

	meshes.emplace_back(Quad(), "res/textures/maze.png", shader);
	meshes.emplace_back(Spike(), "res/textures/th.png", shader);
	meshes[0].transform.position -= glm::vec3(0, 200, 0);

	//-------------------------------------------------------//

	while (!glfwWindowShouldClose(wc.window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

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