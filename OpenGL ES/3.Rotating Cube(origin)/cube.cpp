#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<shader_c.h>//res/shader_s.h
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "cube", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	float vertices[] = {

		-0.5f,0.5f,-0.5f,	0.0f, 0.0f, 0.0f,//��A 0
		-0.5f,0.5f,0.5f,	0.0f, 0.0f, 1.0f,//��B 1
		0.5f,0.5f,-0.5f,	0.0f, 1.0f, 0.0f,//��C 2
		0.5f,0.5f,0.5f,		0.0f, 1.0f, 1.0f,//��D 3

		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,//��E 4
		-0.5f,-0.5f,0.5f,	1.0f, 0.0f, 1.0f,//��F 5
		0.5f,-0.5f,-0.5f,	1.0f, 1.0f, 0.0f,//��G 6
		0.5f,-0.5f,0.5f,	1.0f, 1.0f, 1.0f//��H 7


	};

	unsigned int indices[] = {
		/*����ABC,BCD*/
		0,1,2,
		1,2,3,

		/*����EFG,FGH*/
		4,5,6,
		5,6,7,
		/*�����ABF,AEF*/
		0,1,5,
		0,4,5,
		/*�Ҳ���CDH,CGH*/
		2,3,7,
		2,6,7,
		/*ǰ��ACG,AEG*/
		0,2,6,
		0,4,6,
		/*����BFH,BDH*/
		1,5,7,
		1,3,7
	};

	Shader ourShader("res/shader.vs", "res/shader.fs");

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//λ�ú�������Ӧshader.vs�е�aPos��6��ʾ6���㡣

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//��ɫ��������Ӧshader.vs�е�aColor��6��ʾ6����

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		ourShader.use();

		glm::mat4 transform;
		transform = glm::rotate(transform, 1 * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));//��x��y��z����ʱ����ת��OpenGL����ʱ��Ϊ������

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);//һ�������������Σ�6����12�������Σ�һ��������ռ3�ֽ�

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	return 0;
}