#pragma once
#define STB_IMAGE_IMPLEMENTATION


#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "./Camera/Camera.h"
#include "./Material/Material.h"
#include "./light/LightDirectional.h"
#include "./light/lightPoint.h"
#include "./light/lightSpot.h"
#include "./Mesh/Mesh.h"
#include "Model.h"

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

// class LightDirectional
lightSpot *ltspt = new lightSpot(vec3(0.0f, 5.0f, 0.0f), vec3(radians(90.0f), 0, 0), vec3(1.0f, 1.0f, 1.0f));

LightDirectional *ltdir = new LightDirectional(vec3(1.0f, 1.0f, -1.0f), vec3(radians(45.0f), radians(45.0f), 0), vec3(1.0f, 1.0f, 1.0f));

lightPoint *ltPtr0 = new lightPoint(vec3(1.0f, 1.0f, -1.0f), vec3(radians(45.0f), radians(45.0f), 0), vec3(1.0f, 1.0f, 1.0f));
lightPoint *ltPtr1 = new lightPoint(vec3(0.0f, 1.0f, 0.0f), vec3(radians(45.0f), radians(45.0f), 0), vec3(0.0f, 1.0f, 0.0f));
lightPoint *ltPtr2 = new lightPoint(vec3(0.0f, 0.0f, 1.0f), vec3(radians(45.0f), radians(45.0f), 0), vec3(0.0f, 0.0f, 1.0f));
lightPoint *ltPtr3 = new lightPoint(vec3(1.0f, 0.0f, 0.0f), vec3(radians(45.0f), radians(45.0f), 0), vec3(1.0f, 0.0f, 0.0f));


// vector of lightpoint
std::vector<lightPoint*> buf = {ltPtr0, ltPtr1 , ltPtr2, ltPtr3};

#pragma endregion

#pragma region fun
void prcessInput_Keyboard(GLFWwindow *win) {
	// ?????????????? ESC????
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true); // ????????
	}
	else if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
		camer->speedZ = 0.05f;
		camer->set_Camera_Pos();
		camer->speedZ = 0.0f;
	}
	else if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
		camer->speedZ = -0.05f;
		camer->set_Camera_Pos();
		camer->speedZ = 0.0f;
	}
	else if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
		camer->speedX = -0.05f;
		camer->set_Camera_Pos();
		camer->speedX = 0.0f;
	}
	else if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
		camer->speedX = 0.05f;
		camer->set_Camera_Pos();
		camer->speedX = 0.0f;
	}
	else if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) {
		camer->speedY = -0.05f;
		camer->set_Camera_Pos();
		camer->speedY = 0.0f;
	} 
	else if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS) {
		camer->speedY = 0.05f;
		camer->set_Camera_Pos();
		camer->speedY = 0.0f;
	}
	else {
		camer->speedZ = 0.0f;
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

unsigned int _Create__Texture(const char *file, GLint internalformat, int slot) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);  // ????

	int width, height, nrchannels;
	unsigned char *data = stbi_load(file, &width, &height, &nrchannels, 0);
	if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, internalformat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "failed open image!" << endl;
	}

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);

	//free
	//glActiveTexture(GL_TEXTURE0);
	stbi_image_free(data);
	return texture;
}


void _Create__init(unsigned int& V, const char *_typename) {
	if (_typename == "VAO") {
		glGenVertexArrays(1, &V); // Create one VAO
		glBindVertexArray(V); // ?????? Vertex Shader
	} 

	else if (_typename == "VBO") {
		glGenBuffers(1, &V); // Create one VBO
		glBindBuffer(GL_ARRAY_BUFFER, V); // VBO ????
	}
	else {
		glGenBuffers(1, &V);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, V);
	}
}

// tell OpenGL how to recognize these coordinates.
void _GL__Identfly__stall() {
	 //tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2); 
}
#pragma endregion