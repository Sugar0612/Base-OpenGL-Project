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


	unsigned int ID; // programshader id
};

