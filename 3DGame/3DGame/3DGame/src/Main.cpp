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
	camera.BindProjection(shader);

	Camera camera2(glm::perspective(glm::radians(90.0f), wc.windowSize.x / wc.windowSize.y, 0.1f, 100.0f)); // projection is a common subject for your meshes to not be in the center.

	Time time;

	                  /* Meshes below */
	//-------------------------------------------------------//

	std::vector<Object> objs;

	Mesh CubeMesh(Cube(), "res/textures/th.png");
	Mesh Spike_3DMesh(Spike_3D(), "res/textures/dick.png");
	Mesh SpikeMesh(Spike(), "res/textures/MyStoneTexture.jpg");
	Mesh QuadMesh(Quad(), "res/textures/square.png");

	int width = 10;
	int height = 10;

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			Object a(&CubeMesh);
			a.transform.position = glm::vec3(i, -50, j);

			objs.emplace_back(a);
		}
	}

	//-------------------------------------------------------//

	float movementSpeed = 5.0f;

	double tempx, tempy;
	glm::vec2 m = glm::vec2(0);

	Camera* boundCamera = &camera;

	while (!glfwWindowShouldClose(wc.window))
	{
		std::cout << "camera2: " << camera2.transform.position.x << ", " << camera2.transform.position.y << ", " << camera2.transform.position.z << std::endl;
		std::cout << "camera1: " << camera.transform.position.x << ", " << camera.transform.position.y << ", " << camera.transform.position.z << std::endl;
		std::cout << "boundcamera: " << boundCamera->transform.position.x << ", " << boundCamera->transform.position.y << ", " << boundCamera->transform.position.z << std::endl;

		if (Input::KeyPressed(49, wc.window))
		{
			boundCamera = &camera;
		}
		if (Input::KeyPressed(50, wc.window))
		{
			boundCamera = &camera2;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time.UpdateTime();

		boundCamera->transform.rotation.x += m.x;
		boundCamera->transform.rotation.y += m.y;

		glfwGetCursorPos(wc.window, &tempx, &tempy);

		if(Input::KeyPressed(83, wc.window))
			boundCamera->transform.position -= (boundCamera->forward * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(87, wc.window))
			boundCamera->transform.position += (boundCamera->forward * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(65, wc.window))
			boundCamera->transform.position -= (boundCamera->right * movementSpeed) * time.deltaTime;
		else if (Input::KeyPressed(68, wc.window))
			boundCamera->transform.position += (boundCamera->right * movementSpeed) * time.deltaTime;

		if (Input::KeyPressed(32, wc.window))
			boundCamera->transform.position.y += movementSpeed * time.deltaTime;
		else if (Input::KeyPressed(340, wc.window))
			boundCamera->transform.position.y -= movementSpeed * time.deltaTime;


		for (size_t i = 0; i < objs.size(); i++)
		{
			objs[i].Draw(shader);
		}

		glfwSwapBuffers(wc.window); // Dont render anything after swapping the buffers.

		boundCamera->CalculateMatrices(shader);
		glfwPollEvents();

		m = Input::UpdateMouse(glm::vec2(tempx, tempy), wc.window);
	}

	glfwTerminate();
	return 0;
}