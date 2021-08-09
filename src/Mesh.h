#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 positoin;
	vec3 normal;
	vec2 texCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> idxes;
	vector<Texture> textures;
	
	Mesh(vector<Vertex> vertices_, vector<unsigned int> idx, vector<Texture> textures_);
	void Draw(Shader *myShader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

