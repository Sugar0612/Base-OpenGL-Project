#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

using namespace::std;

class Shader
{
public:
	Shader(const char *vertexfile, const char *fragmentfile);
	~Shader() = default;
	void useProgram();
	void setVec3(string Uniform_name, float x, float y, float z); // push lighting-color uniform.

	unsigned int ID; // programshader id
private:
	void _check_Compile_Error(unsigned int id, string type);
};

