#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


using namespace::std;
using namespace::glm;

class Shader
{
public:
	Shader(const char *vertexfile, const char *fragmentfile);
	~Shader() = default;
	void useProgram();

	
	void setVec3(string Uniform_name, vec3 vector_3); // push lighting-color uniform.
	void setVec1(string Uniform_name, float power); // enlarge light's specular.

	unsigned int ID; // programshader id
private:
	void _check_Compile_Error(unsigned int id, string type);
};

