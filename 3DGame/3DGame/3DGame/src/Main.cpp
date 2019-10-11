#include "WindowCreation.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Shapes.h"
#include "Renderer2D.h"

int main()
{

	// WindowCreation should be first 99% of the time.
	WindowCreation wc(glm::vec2(1080, 1080));

	Shader shader("res/shaders/shader.shader");
	shader.Bind();

	Camera camera(glm::perspective(glm::radians(90.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f)); // projection is a common subject for your meshes to not be in the center.
	camera.Bind(shader);

	                  /* Meshes below */
	//-------------------------------------------------------//

	std::vector<Mesh> meshes;

	meshes.emplace_back(Spike_3D(), "res/textures/th.png", shader);
	meshes.emplace_back(Cube(), "res/textures/th.png", shader);

	meshes[0].transform.position = glm::vec3(0, 0, 0);
	meshes[1].transform.position = glm::vec3(0, -1, 0);

	//-------------------------------------------------------//

	float movementSpeed = 1;

	double tempx, tempy;
	glm::vec2 m = glm::vec2(0);

	while (!glfwWindowShouldClose(wc.window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::cout << m.x << ", " << m.y << std::endl;

		camera.transform.rotation.x += m.x;
		camera.transform.rotation.y += m.y;

		glfwGetCursorPos(wc.window, &tempx, &tempy);

		if(Input::KeyPressed(83, wc.window))
			camera.transform.position.z += camera.forward.z * movementSpeed;
		else if(Input::KeyPressed(87, wc.window))
			camera.transform.position.z -= camera.forward.z * movementSpeed;

		if (Input::KeyPressed(68, wc.window))
			camera.transform.position.x += camera.right.x * movementSpeed;
		else if (Input::KeyPressed(65, wc.window))
			camera.transform.position.x -= camera.right.x * movementSpeed;

		if (Input::KeyPressed(32, wc.window))
			camera.transform.position.y += camera.up.y * movementSpeed;
		else if (Input::KeyPressed(340, wc.window))
			camera.transform.position.y -= camera.up.y * movementSpeed;


		for (size_t i = 0; i < meshes.size(); i++)
		{

			if (meshes[i].renderMe)
				meshes[i].Draw();
		}

		glfwSwapBuffers(wc.window); // Dont render anything after swapping the buffers.

		camera.CalculateMatrices(shader);
		glfwPollEvents();

		m = Input::UpdateMouse(glm::vec2(tempx, tempy), wc.window);
	}

	glfwTerminate();
	return 0;
}