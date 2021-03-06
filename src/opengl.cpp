#define GLEW_STATIC  // 使用 glew32s.lib静态库
#include "opengl.h"
#include "./Shader/Shader.h"

int main(int argc, char *argv[]) {
	string exePath = argv[0];

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
		//Material *material = new Material(myShader, vec3(0.2f, 0.2f, 0.2f), _Create__Texture("./model/diffuse.jpg", GL_RGB, 0), _Create__Texture("./sourceImage/container_specular.png", GL_RGBA, 1), 32);
	#pragma endregion

	#pragma region Init Mesh and Model
		string path = "./model/backpack.obj";
		Model *model = new Model(path);
#pragma endregion

	#pragma region Init VAO, VBO and EBO.
	//// Create VAO and VBO  (VBO ==> VAO)
	//unsigned int VAO;
	//_Create__init(VAO, "VAO");

	//unsigned int VBO;
	//_Create__init(VBO,  "VBO");
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将 vertices 数据放到 VBO中


	//// Create EBO (EBO ==> VAO)
	//unsigned int EBO;
	//_Create__init(EBO, "EBO");
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
#pragma endregion


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

			// Shader Program
			myShader->useProgram();

			// Insert the specified Uniform.
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, value_ptr(projMat));
			myShader->setVec3("objColor", vec3(1.0f, 1.0f, 1.0f));
			myShader->setVec3("ambientColor", vec3(1.0f, 1.0f, 1.0f));

			myShader->setVec3("CameraPos", camer->camera_Pos);

			myShader->setVec3("lightD.pos", ltdir->position);
			myShader->setVec3("lightD.color", ltdir->color);
			myShader->setVec3("lightD.dir", ltdir->direction);

			for (int i = 0; i < buf.size(); ++i) {
				string lightpt = "lightPt[" + to_string(i);
				string pos = "].pos";
				string color = "].color";
				string dir = "].dir";
				string constant = "].constant";
				string linear = "].linear";
				string quadratic = "].quadratic";
				myShader->setVec3(lightpt + pos, buf[i]->position);
				myShader->setVec3(lightpt + color, buf[i]->color);
				myShader->setVec3(lightpt + dir, buf[i]->direction);
				myShader->setVec1(lightpt + constant, buf[i]->constant);
				myShader->setVec1(lightpt + linear, buf[i]->linear);
				myShader->setVec1(lightpt + quadratic, buf[i]->quadratic);
			}

			myShader->setVec3("lightSp.pos", ltspt->position);
			myShader->setVec3("lightSp.color", ltspt->color);
			myShader->setVec3("lightSp.dir", ltspt->direction);
			myShader->setVec1("lightSp.constant", ltspt->constant);
			myShader->setVec1("lightSp.linear", ltspt->linear);
			myShader->setVec1("lightSp.qeadratic", ltspt->qeadratic);
			myShader->setVec1("lightSp.cosPhyInner", ltspt->cosPhyInner);
			myShader->setVec1("lightSp.cosPhyOutter", ltspt->cosPhyOutter);

			myShader->setVec3("material.ambient", vec3(0.5, 0.5, 0.5));
			//material->myShader->setUniform1i("marterial.diffuse", 0);
			//material->myShader->setUniform1i("marterial.specular", 1);
			myShader->setVec1("material.shininess", 32.0f);

			//mesh->Draw(material->myShader);
			model->Draw(myShader);
			break;
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