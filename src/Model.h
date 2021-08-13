#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./Mesh/Mesh.h"
#include "./Shader/Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;
using namespace::Assimp;


class Model
{
	void proessNode(aiNode *node, const aiScene *scene);
	Mesh proessMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, string type_name);
	unsigned int GetTextrueID(const char *path);
	void LoadModel(const string path);
	string directory;

	vector<Mesh> meshes;
	vector<Texture> texture_loaded;
public:
	Model(const string &path);
	void Draw(Shader *myShader);
	~Model();

};
#endif // MODEL_H
