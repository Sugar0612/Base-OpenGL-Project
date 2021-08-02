#include "Shader.h"

Shader::Shader(const char *vertexfile, const char *fragmentfile) {
	ifstream vertexSfile, fragmentSfile;
	string vertexCode, fragmentCode;
	const char *vertexScode, *fragmentScode;

	try {
		vertexSfile.open(vertexfile);
		fragmentSfile.open(fragmentfile);

		//if not open Source file
		if ((!vertexSfile.is_open()) || (!fragmentSfile.is_open())) {
			throw exception("failed Shader file open!");
		}

		stringstream vertexSstream, fragmentSstream;
		vertexSstream << vertexSfile.rdbuf();
		fragmentSstream << fragmentSfile.rdbuf();

		vertexSfile.close();
		fragmentSfile.close();

		vertexCode = vertexSstream.str();
		fragmentCode = fragmentSstream.str();

		vertexScode = vertexCode.c_str();
		fragmentScode = fragmentCode.c_str();
		
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexScode, nullptr);
		glCompileShader(vertex);
		_check_Compile_Error(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentScode, nullptr);
		glCompileShader(fragment);
		_check_Compile_Error(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		_check_Compile_Error(ID, "PROGRAM");
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
}

void Shader::useProgram() {
	glUseProgram(ID);
}


void Shader::_check_Compile_Error(unsigned int id, string type) {
	int success;
	char errorInfo[1024];
	
	if (type != "PROGRAM") {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(id, 1024, nullptr, errorInfo);
			cout << "failed compile : " << errorInfo << endl;
		}
	}

	else {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 1024, nullptr, errorInfo);
			cout << "failed program linking : " << errorInfo << endl;
		}
	}
}


void Shader::setVec3(string Uniform_name, vec3 vector_3) {
	glUniform3f(glGetUniformLocation(ID, Uniform_name.c_str()), vector_3.x, vector_3.y, vector_3.z);
}

void Shader::setVec1(string Uniform_name, float power)
{
	glUniform1f(glGetUniformLocation(ID, Uniform_name.c_str()), power);
}

void Shader::setUniform1i(string Uniform_name, int slot)
{
	glUniform1i(glGetUniformLocation(ID, Uniform_name.c_str()), slot);
}
