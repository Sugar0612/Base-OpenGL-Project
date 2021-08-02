#pragma once
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace::glm;

class Material
{
public:
	Shader *myShader;
	vec3 anbiemt;
	unsigned int diffuse;
	unsigned int specular;
	float shininess;

	Material(Shader *&myShader, vec3 _anbiemt, unsigned int _diffuse, unsigned int _specular, float _shininess);
};

