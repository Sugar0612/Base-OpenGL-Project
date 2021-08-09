#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices_, vector<unsigned int> idx, vector<Texture> textures_) :
	vertices(vertices_), idxes(idx), textures(textures_)
{
	
	setupMesh();
}

void Mesh::Draw(Shader *myShader)
{
	for (int i = 0; i < textures.size(); ++i) {
		string name = textures[i].type;
		if (name == "texture_diffues") {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE0, textures[i].id);
			myShader->setUniform1i("material.diffuse", 0);
		}
		else if (name == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE1, textures[i].id);
			myShader->setUniform1i("material.spcular", 1);
		}
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, idxes.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Texture) * idxes.size(), &idxes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)3);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)6);

	glBindVertexArray(0);
}
