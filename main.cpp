#define GLEW_STATIC  // 使用 glew32s.lib静态库

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

using namespace::std;

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

	// 如果glfwWin 没有正常关闭
	while (!glfwWindowShouldClose(glfwWin)) {
		// 消除屏幕因为渲染出现伪影的状况(two buffers)。
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // 获取用户的操作
	}

	glfwTerminate();
	return 0;
}