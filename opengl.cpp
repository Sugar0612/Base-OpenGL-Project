#define GLEW_STATIC  // ʹ�� glew32s.lib��̬��
#include "opengl.h"
#include "Shader.h"

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
	Shader *myShader = new Shader("./shaderSource/vertexSource.txt", "./shaderSource/fragmentSource.txt");

	// Draw line
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	//// �޳�ĳ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Create VAO and VBO  (VBO ==> VAO)
	unsigned int VAO;
	_Create__init(VAO, "VAO");

	unsigned int VBO;
	_Create__init(VBO,  "VBO");
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �� vertices ���ݷŵ� VBO��


	// Create EBO (EBO ==> VAO)
	unsigned int EBO;
	_Create__init(EBO, "EBO");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	//tell opengl identfly the stall
	_GL__Identfly__stall();

	// Create and Bind texBuffer and faceBuffer.
	unsigned int texBuffer = 0, faceBuffer = 0;
	_Create__Texture(texBuffer, "./sourceImage/container.jpg", "jpg");
	_Create__Texture(faceBuffer, "./sourceImage/awesomeface.png", "png");


	// ���glfwWin û�йر� ������״̬
	while (!glfwWindowShouldClose(glfwWin)) {
		/*mat4 modelMat;
		modelMat = rotate(modelMat, radians(55.0f), vec3(0.1, 0.4, 0.6));*/
		mat4 viewMat;
		viewMat = translate(viewMat, vec3(0.0f, 0.0f, -3.0f));
		mat4 projMat;
		projMat = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		// This is an identity matrix.
		/*mat4 trans;
		trans = scale(trans, glm::vec3(0.5, 0.5, 0.5));
		trans = translate(trans, vec3(0.5f, -0.5f, 0));
		trans = rotate(trans, (float)glfwGetTime(), vec3(0, 0, 1.0f));*/


		pressInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBuffer);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceBuffer);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // triangles
		myShader->useProgram();


		// draw use VAO
		glBindVertexArray(VAO);

		// looper rendering ten cube.
		for (int i = 1; i <= 10; ++i) {
			float angle = i * 25.0f;

			mat4 modelMat;
			modelMat = translate(modelMat, cubePositions[i - 1]);

			modelMat = rotate(modelMat, (float)(glfwGetTime() * radians(angle)), vec3(0.5f, 1.0f, 0.3f));

			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glUniform1i(glGetUniformLocation(myShader->ID, "aTex"), 0);
		glUniform1i(glGetUniformLocation(myShader->ID, "aface"), 1);
		//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, value_ptr(trans));

		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, value_ptr(projMat));
		//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));

		// enable depth_test
		glEnable(GL_DEPTH_TEST);
		

		// draw Triangles use EBO
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ������Ļ��Ϊ��Ⱦ����αӰ��״��(two buffers)��
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // ��ȡ�û��Ĳ���
	}

	glfwTerminate();
	return 0;
}