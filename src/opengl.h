#pragma once
#define STB_IMAGE_IMPLEMENTATION


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"

using namespace::std;

using namespace::glm;

#pragma region Model data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

// draw index 
unsigned int index[] = {
	0, 1, 2,
	2, 3, 0
};


vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Declare
//Create Camera
Camera *camer = new Camera(vec3(0, 0, 3.0f), 0.0f, 180.0f, vec3(0, 1.0f, 0));

// dirtion
float dirX = 0.0f, dirY = 0.0f;

// last to x and y
float last_x = 0.0f, last_y = 0.0f;

bool first_cursor_input = true;

unsigned int containerTex;
#pragma endregion

#pragma region fun
void prcessInput_Keyboard(GLFWwindow *win) {
	// 如果用户按下了 ESC按钮
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true); // 关闭窗口
	}
	else if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
		camer->camera_Pos += camer->forWord * (0.01f);
	}
	else if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
		camer->camera_Pos -= camer->forWord * (0.01f);
	}
	else if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
		camer->camera_Pos += normalize(cross(camer->forWord, camer->up)) * (0.01f);
	}
	else if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
		camer->camera_Pos -= normalize(cross(camer->forWord, camer->up)) * (0.01f);
	}
	else if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) {
		camer->camera_Pos -= camer->up * (0.01f);
	} 
	else if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS) {
		camer->camera_Pos += camer->up * (0.01f);
	}
	else {
		camer->speed_z = 0.0f;
	}
	return;
}


void mouse_callback(GLFWwindow* w, double mouseX, double mouseY) {
	dirX = mouseX - last_x;
	dirY = mouseY - last_y;

	last_x = mouseX;
	last_y = mouseY;

	camer->setViewPos(dirX, dirY);
	return;
}

void _Create__Texture(unsigned int &texture, const char *file, GLint internalformat) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);  // 翻转

	unsigned char *data = stbi_load(file, &width, &height, &nrchannels, 0);
	if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, internalformat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
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

// tell OpenGL how to recognize these coordinates.
void _GL__Identfly__stall() {
	// tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2); 
}
#pragma endregion