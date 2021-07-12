#define GLEW_STATIC  // 使用 glew32s.lib静态库

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
using namespace::std;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};  // 三角形坐标

// Src (vertex and fragment)
const char *vertexShaderSource = 
	"#version 330 core \n"
    "layout (location = 0) in vec3 aPos; \n"
    "void main(){ \n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";


const char *fragmentShaderSource =
"#version 330 core	\n						  "
"out vec4 FragColor;	\n					  "
"void main(){			\n					  "
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\n";



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

	// Create VAO and VBO  (VBO ==> VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // Create one VAO
	glBindVertexArray(VAO); // 连接到 Vertex Shader

	unsigned int VBO;
	glGenBuffers(1, &VBO); // Create one VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO 类型
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将 vertices 数据放到 VBO中

	// Create vertexShader and fragmentShader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); // 编译

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); // 编译

	// Link vertexShader and fragmentShader use shaderProgram
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

																					 
	// 如果glfwWin 没有关闭 在运行状态
	while (!glfwWindowShouldClose(glfwWin)) {
		pressInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw Triangle
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3); // triangles

		// 消除屏幕因为渲染出现伪影的状况(two buffers)。
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // 获取用户的操作
	}

	glfwTerminate();
	return 0;
}