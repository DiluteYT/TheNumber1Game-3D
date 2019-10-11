#include "WindowCreation.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Shapes.h"
#include "Renderer2D.h"
#include "Time.h"

int main()
{

	// WindowCreation should be first 99% of the time.
	WindowCreation wc(glm::vec2(1080, 1080));

	Shader shader("res/shaders/shader.shader");
	shader.Bind();

	Camera camera(glm::perspective(glm::radians(90.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f)); // projection is a common subject for your meshes to not be in the center.
	camera.Bind(shader);

	Time time;

	                  /* Meshes below */
	//-------------------------------------------------------//

	std::vector<Mesh> meshes;

	meshes.emplace_back(Cube(), "res/textures/th.png", shader);
	meshes.emplace_back(Spike_3D(), "res/textures/dick.png", shader);
	meshes.emplace_back(Spike(), "res/textures/MyStoneTexture.jpg", shader);
	meshes.emplace_back(Quad(), "res/textures/square.png", shader);

	meshes[0].transform.position.x -= 2;
	meshes[1].transform.position.x += 2;

	meshes[2].transform.position += glm::vec3(2.0f, 0, -4.0f);
	meshes[3].transform.position += glm::vec3(-2.0f, 0, -4.0f);

	//-------------------------------------------------------//

	float movementSpeed = 5.0f;

	double tempx, tempy;
	glm::vec2 m = glm::vec2(0);

	while (!glfwWindowShouldClose(wc.window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time.UpdateTime();

		camera.transform.rotation.x += m.x;
		camera.transform.rotation.y += m.y;

		glfwGetCursorPos(wc.window, &tempx, &tempy);

		if(Input::KeyPressed(83, wc.window))
			camera.transform.position -= (camera.forward * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(87, wc.window))
			camera.transform.position += (camera.forward * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(65, wc.window))
			camera.transform.position -= (camera.right * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(68, wc.window))
			camera.transform.position += (camera.right * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(32, wc.window))
			camera.transform.position.y += movementSpeed * time.deltaTime;
		else if (Input::KeyPressed(340, wc.window))
			camera.transform.position.y -= movementSpeed * time.deltaTime;

		meshes[0].transform.rotation += glm::vec3(0.01f, 0.01f, 0);
		meshes[1].transform.rotation += glm::vec3(0.02f, 0.02f, 0);
		meshes[2].transform.rotation += glm::vec3(0.04f, 0.04f, 0);
		meshes[3].transform.rotation += glm::vec3(0.08f, 0.08f, 0);

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