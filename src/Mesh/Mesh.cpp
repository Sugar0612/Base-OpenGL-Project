#include "Mesh.h"

Mesh::Mesh(float vertices_[])
{
	this->vertices.resize(36);
	memcpy(&(this->vertices[0]), vertices_, 36 * 8 * sizeof(float));
	setupMesh();
	/*for (int i = 0; i < 36; ++i) {
		int row = i * 8;
		vertices[i].positoin = vec3(vertices_[row + 0], vertices_[row + 1], vertices_[row + 2]);
		vertices[i].normal = vec3(vertices_[row + 3], vertices_[row + 4], vertices_[row + 5]);
		vertices[i].texCoords = vec2(vertices_[row + 6], vertices_[row + 7]);
	}*/
}

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
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	/*glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Texture) * idxes.size(), &idxes[0], GL_STATIC_DRAW);*/

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));

	glBindVertexArray(0);
}
