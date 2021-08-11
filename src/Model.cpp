#include "Model.h"

Model::Model(const string & path)
{
	LoadModel(path);
}

Model::~Model()
{
}

void Model::proessNode(aiNode *node, const aiScene *scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(proessMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; ++i) {
		proessNode(node->mChildren[i], scene);
	}
}

Mesh Model::proessMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertex;
	vector<unsigned int> idxes;
	vector<Texture> textures;

	for (int i = 0; i < mesh->mNumVertices; ++i) {
		Vertex buf;
		aiVector3D vector3 = mesh->mVertices[i];
		aiVector3D normal;
		aiVector3D texture;
		buf.positoin = vec3(vector3.x, vector3.y, vector3.z);

		if (mesh->HasNormals()) {
			normal = mesh->mNormals[i];
			buf.normal = vec3(normal.x, normal.y, normal.z);
		}

		if (mesh->mTextureCoords[0]) {
			texture = mesh->mTextureCoords[0][i];
			buf.texCoords = vec2(texture.x, texture.y);
		}
		else {
			buf.texCoords = vec2(0.0f, 0.0f);
		}
		vertex.emplace_back(buf);
	}

	for (int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j) {
			idxes.emplace_back(face.mIndices[j]);
		}
	}

	return Mesh(vertex, idxes, {});

}

void Model::LoadModel(const string path)
{
	Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "failed model flie! error is : " << importer.GetErrorString() << endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));
	proessNode(scene->mRootNode, scene);
}


void Model::Draw(Shader * myShader)
{
	for (int i = 0; i < meshes.size(); ++i) {
		meshes[i].Draw(myShader);
	}
}