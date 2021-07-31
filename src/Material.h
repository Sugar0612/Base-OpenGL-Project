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
	vec3 diffuse;
	vec3 specular;
	float shininess;

	Material(Shader *&myShader, vec3 _anbiemt, vec3 _diffuse, vec3 _specular, float _shininess);
};

