#define GLEW_STATIC  // 使用 glew32s.lib静态库
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"

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
	// 如果用户按下了 ESC按钮
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true); // 关闭窗口
	}
	return;
}


int main() {
	glfwInit(); // 初始化第三方库 glfw

	// 版本号 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 关于profile的类型

	GLFWwindow *glfwWin = glfwCreateWindow(800, 600, "myOpenGL", nullptr, nullptr); // 创建窗口

	// 如果 窗口为空
	if (glfwWin == nullptr) {
		cout << "error window" << endl;
		glfwTerminate(); // 停止glfwWin 窗口
		return -1;
	}

	glfwMakeContextCurrent(glfwWin); // 绑定成 主要窗口

	// Init Glew
	glewExperimental = true;
																					 
	// If glew is failed															 
	if (glewInit() != GLEW_OK) {													 
		cout << "error glew!" << endl;												 
		glfwTerminate();  // stop glfw window										 
		return -1;																	 
	}

	glViewport(0, 0, 800, 600); // 设置窗口像素值 (第三参数 第四参数是 渲染宽高的像素值)
	Shader *myShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	// Draw line
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	//// 剔除某个面
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Create VAO and VBO  (VBO ==> VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // Create one VAO
	glBindVertexArray(VAO); // 连接到 Vertex Shader

	unsigned int VBO;
	glGenBuffers(1, &VBO); // Create one VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO 类型
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将 vertices 数据放到 VBO中

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

	// Create and Bind texBuffer.
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);
	glBindTexture(GL_TEXTURE_2D, texBuffer);

	int width, height, nrchannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrchannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "failed open image!" << endl;
	}

	//free
	stbi_image_free(data);

	// 如果glfwWin 没有关闭 在运行状态
	while (!glfwWindowShouldClose(glfwWin)) {
		pressInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindTexture(GL_TEXTURE_2D, texBuffer);
		// draw use VAO
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // triangles
		myShader->useProgram();

		// draw Triangles use EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 消除屏幕因为渲染出现伪影的状况(two buffers)。
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // 获取用户的操作
	}

	glfwTerminate();
	return 0;
}