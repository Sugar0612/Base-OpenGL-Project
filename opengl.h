#pragma once
#define STB_IMAGE_IMPLEMENTATION


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace::std;

using namespace::glm;

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

// draw index 
unsigned int index[] = {
	0, 1, 2,
	2, 3, 0
};


void _Create__Texture(unsigned int &texture, const char *file, string file_type) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);  // 翻转

	unsigned char *data = stbi_load(file, &width, &height, &nrchannels, 0);
	if (data) {
		if (file_type == "png") {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else {
		cout << "failed open image!" << endl;
	}

	//free
	stbi_image_free(data);
}


void _Create__init(unsigned int& V, const char *_typename) {
	if (_typename == "VAO") {
		glGenVertexArrays(1, &V); // Create one VAO
		glBindVertexArray(V); // 连接到 Vertex Shader
	} 

	else if (_typename == "VBO") {
		glGenBuffers(1, &V); // Create one VBO
		glBindBuffer(GL_ARRAY_BUFFER, V); // VBO 类型
	}
	else {
		glGenBuffers(1, &V);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, V);
	}
}


void _GL__Identfly__stall() {
	// tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// tell OpenGL it should interpret the vertex of color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// tell OpenGL it should interpret the texture of Postion data
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
