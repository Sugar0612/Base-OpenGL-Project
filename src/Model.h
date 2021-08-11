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

using namespace std;
using namespace::Assimp;


class Model
{
	void proessNode(aiNode *node, const aiScene *scene);
	Mesh proessMesh(aiMesh *mesh, const aiScene *scene);
	void LoadModel(const string path);
	string directory;

	vector<Mesh> meshes;
public:
	Model(const string &path);
	void Draw(Shader *myShader);
	~Model();

};
#endif // MODEL_H
