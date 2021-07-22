#define GLEW_STATIC  // ʹ�� glew32s.lib��̬��

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "opengl.h"
#include "Shader.h"

using namespace::std;

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



void pressInput_Keyboard(GLFWwindow *win) {
	// ����û������� ESC��ť
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true); // �رմ���
	}
	return;
}


int main() {
	glfwInit(); // ��ʼ���������� glfw

	// �汾�� 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ����profile������

	GLFWwindow *glfwWin = glfwCreateWindow(800, 600, "myOpenGL", nullptr, nullptr); // ��������

	// ��� ����Ϊ��
	if (glfwWin == nullptr) {
		cout << "error window" << endl;
		glfwTerminate(); // ֹͣglfwWin ����
		return -1;
	}

	glfwMakeContextCurrent(glfwWin); // �󶨳� ��Ҫ����

	// Init Glew
	glewExperimental = true;
																					 
	// If glew is failed															 
	if (glewInit() != GLEW_OK) {													 
		cout << "error glew!" << endl;												 
		glfwTerminate();  // stop glfw window										 
		return -1;																	 
	}

	glViewport(0, 0, 800, 600); // ���ô�������ֵ (�������� ���Ĳ����� ��Ⱦ��ߵ�����ֵ)
	Shader *myShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	// Draw line
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	//// �޳�ĳ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Create VAO and VBO  (VBO ==> VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // Create one VAO
	glBindVertexArray(VAO); // ���ӵ� Vertex Shader

	unsigned int VBO;
	glGenBuffers(1, &VBO); // Create one VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �� vertices ���ݷŵ� VBO��

	// Create EBO (EBO ==> VAO)
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);


	// tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	// tell OpenGL it should interpret the vertex of color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// tell OpenGL it should interpret the texture of Postion data
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Create and Bind texBuffer and faceBuffer.
	unsigned int texBuffer = 0, faceBuffer = 0;
	_Create_Texture(texBuffer, "container.jpg", "jpg");
	_Create_Texture(faceBuffer, "awesomeface.png", "png");

	// ���glfwWin û�йر� ������״̬
	while (!glfwWindowShouldClose(glfwWin)) {
		pressInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBuffer);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceBuffer);

		// draw use VAO
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // triangles
		myShader->useProgram();
		glUniform1i(glGetUniformLocation(myShader->ID, "aTex"), 0);
		glUniform1i(glGetUniformLocation(myShader->ID, "aface"), 1);


		// draw Triangles use EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ������Ļ��Ϊ��Ⱦ����αӰ��״��(two buffers)��
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // ��ȡ�û��Ĳ���
	}

	glfwTerminate();
	return 0;
}