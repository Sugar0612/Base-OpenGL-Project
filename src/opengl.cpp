#define GLEW_STATIC  // 使用 glew32s.lib静态库
#include "opengl.h"
#include "Shader.h"

int main() {
	#pragma region Open the Window
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

	glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // MOUSE DISABLED.
	glViewport(0, 0, 800, 600); // 设置窗口像素值 (第三参数 第四参数是 渲染宽高的像素值)

	glfwSetCursorPosCallback(glfwWin, mouse_callback);
#pragma endregion

	#pragma region Init myShader
		Shader *myShader = new Shader("./shaderSource/vertexSource.vert", "./shaderSource/fragmentSource.frag");
	#pragma endregion

	#pragma region Init Material
		Material *material = new Material(myShader, vec3(1.0f, 1.0f, 1.0f), _Create__Texture("./sourceImage/container2.png", GL_RGBA, 0), _Create__Texture("./sourceImage/container_specular.png", GL_RGBA, 1), 32);
	#pragma endregion

	#pragma region Init VAO, VBO and EBO.
	// Create VAO and VBO  (VBO ==> VAO)
	unsigned int VAO;
	_Create__init(VAO, "VAO");

	unsigned int VBO;
	_Create__init(VBO,  "VBO");
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将 vertices 数据放到 VBO中


	// Create EBO (EBO ==> VAO)
	unsigned int EBO;
	_Create__init(EBO, "EBO");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
#pragma endregion

	//tell opengl identfly the stall
	_GL__Identfly__stall();


	// 如果glfwWin 没有关闭 在运行状态
	while (!glfwWindowShouldClose(glfwWin)) {
		//Get the user's keys.
		prcessInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// looper rendering ten cube.
		for (int i = 1; i <= 10; ++i) {
			float angle = 0 * 25.0f;

			// Init martix
			mat4 modelMat = mat4(1.0f);
			mat4 viewMat = mat4(1.0f);
			mat4 projMat = mat4(1.0f);
			viewMat = camer->getViewMatrix();
			projMat = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


			// Set model martix
			modelMat = translate(modelMat, cubePositions[i - 1]);
			modelMat = rotate(modelMat, (float)(glfwGetTime()) * radians(angle), vec3(0.5f, 1.0f, 0.3f));

			//load Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->diffuse);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, material->specular);

			// Shader Program
			myShader->useProgram();


			// draw use VAO
			glBindVertexArray(VAO);

			//Drawfun call
			glDrawArrays(GL_TRIANGLES, 0, 36);


			// Insert the specified Uniform.
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, value_ptr(projMat));
			myShader->setVec3("objColor", vec3(1.0f, 1.0f, 1.0f));
			myShader->setVec3("ambientColor", vec3(0.1f, 0.1f, 0.1f));
			myShader->setVec3("lightPos", ltspt->position);
			myShader->setVec3("lightColor", ltspt->color);
			myShader->setVec3("lightDirUniform", ltspt->direction);

			myShader->setVec3("CameraPos", camer->camera_Pos);

			//myShader->setVec1("lightPt.constant", ltptr->constant);
			//myShader->setVec1("lightPt.linear", ltptr->linear);
			//myShader->setVec1("lightPt.quadratic", ltptr->quadratic);

			myShader->setVec1("lightSp.cosPhyInner", ltspt->cosPhyInner);
			myShader->setVec1("lightSp.cosPhyOutter", ltspt->cosPhyOutter);

			material->myShader->setVec3("material.ambient", material->anbiemt);
			material->myShader->setUniform1i("marterial.diffuse", 0);
			material->myShader->setUniform1i("marterial.specular", 1);
			material->myShader->setVec1("material.shininess", 32.0f);
		}

		// enable depth_test
		glEnable(GL_DEPTH_TEST);
		

		// 消除屏幕因为渲染出现伪影的状况(two buffers)。
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // 获取用户的操作

	}

	glfwTerminate();
	return 0;
}