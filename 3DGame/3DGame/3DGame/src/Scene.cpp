#include "Scene.h"

Scene::Scene(WindowCreation& WC, Shader& shader)
	:	SceneCamera(glm::perspective(glm::radians(90.0f), WC.windowSize.x / WC.windowSize.y, 0.1f, 100.0f), shader)
{
}

void Scene::Update()
{
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		if (Meshes[i].Objects.size() < 1)
			return;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Meshes[i].Mesh_Texture.ID);
		glBindVertexArray(Meshes[i].mesh_VAO);
		if (Meshes[i].instanced)
		{
			Meshes[i].meshShader.SetUniformInteger("instanced", true);

			Meshes[i].instancingSetup();
			glDrawArraysInstanced(GL_TRIANGLES, 0, Meshes[i].Vertices.size(), Meshes[i].Objects.size());


		} 
		else {
			Meshes[i].meshShader.SetUniformInteger("instanced", false);
			for (size_t j = 0; j < Meshes[i].Objects.size(); j++)
			{
				Meshes[i].meshShader.SetUniformMatrix4fv("model", Meshes[i].Objects[j].transform.to_mat4());
				glDrawArrays(GL_TRIANGLES, 0, Meshes[i].Vertices.size());
			}
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}