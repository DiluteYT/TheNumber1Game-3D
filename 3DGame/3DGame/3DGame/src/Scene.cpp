#include "Scene.h"
#include "WindowCreation.h"

Scene::Scene(WindowCreation* WC, Shader* shader)
	:	SceneCamera(glm::perspective(glm::radians(90.0f), WC->windowSize.x / WC->windowSize.y, 0.1f, 1000.0f), *shader)
{
}

void Scene::Update()
{
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		if (Meshes[i].modelMatrices.size() < 1)
			return;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Meshes[i].Mesh_Texture.ID);
		glBindVertexArray(Meshes[i].mesh_VAO);
		if (Meshes[i].instanced)
		{
			Meshes[i].meshShader.SetUniformInteger("instanced", true);
			glDrawArraysInstanced(GL_TRIANGLES, 0, Meshes[i].Vertices.size(), Meshes[i].modelMatrices.size());


		} 
		else {
			Meshes[i].meshShader.SetUniformInteger("instanced", false);
			for (size_t j = 0; j < Meshes[i].modelMatrices.size(); j++)
			{
				Meshes[i].meshShader.SetUniformMatrix4fv("model", Meshes[i].modelMatrices[j]);
				glDrawArrays(GL_TRIANGLES, 0, Meshes[i].Vertices.size());
			}
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}