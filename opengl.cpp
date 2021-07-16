#define GLEW_STATIC  // ʹ�� glew32s.lib��̬��

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
using namespace::std;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 //0.5f, -0.5f, 0.0f,
	 //0.0f,  0.5f, 0.0f,
	 0.8f, 0.6f, 0.0f
};  // ����������

// draw index 
unsigned int index[] = {
	0, 1, 2,
	1, 2, 3
};

// Src (vertex and fragment)
const char *vertexShaderSource = 
	"#version 330 core \n"
    "layout (location = 0) in vec3 aPos; \n"
	"out vec4 vertexColor;					\n"
    "void main(){ \n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);  \n"
	"	vertexColor = vec4(1.0, 0, 0, 1.0); \n"
"} \n ";


const char *fragmentShaderSource =
"#version 330 core	\n						  "
"in vec4 vertexColor;		\n				  "
"uniform vec4 ourColor;    \n				  "
"out vec4 FragColor;	\n					  "
"void main(){			\n					  "
"	FragColor = ourColor;}	\n			  ";



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

	// Create vertexShader and fragmentShader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); // ����

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); // ����

	// Link vertexShader and fragmentShader use shaderProgram
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// tell OpenGL it should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

																					 
	// ���glfwWin û�йر� ������״̬
	while (!glfwWindowShouldClose(glfwWin)) {
		pressInput_Keyboard(glfwWin);  // press Esc_Button close glfw_window

		// color rendering
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw Triangle use VBO
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6); // triangles

		// ���ö�ʱ��������˸��ɫ
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int ColorPos = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);

		glUniform4f(ColorPos, 1.0f, greenValue, 0.0f, 1.0f);

		// draw Triangles use EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ������Ļ��Ϊ��Ⱦ����αӰ��״��(two buffers)��
		glfwSwapBuffers(glfwWin); 
		glfwPollEvents(); // ��ȡ�û��Ĳ���
	}

	glfwTerminate();
	return 0;
}