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
			throw exception("failed file open!");
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

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentScode, nullptr);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
}

void Shader::useProgram() {
	glUseProgram(ID);
}