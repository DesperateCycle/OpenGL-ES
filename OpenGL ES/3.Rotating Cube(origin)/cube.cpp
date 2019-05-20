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

		-0.5f,0.5f,-0.5f,	0.0f, 0.0f, 0.0f,//点A 0
		-0.5f,0.5f,0.5f,	0.0f, 0.0f, 1.0f,//点B 1
		0.5f,0.5f,-0.5f,	0.0f, 1.0f, 0.0f,//点C 2
		0.5f,0.5f,0.5f,		0.0f, 1.0f, 1.0f,//点D 3

		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,//点E 4
		-0.5f,-0.5f,0.5f,	1.0f, 0.0f, 1.0f,//点F 5
		0.5f,-0.5f,-0.5f,	1.0f, 1.0f, 0.0f,//点G 6
		0.5f,-0.5f,0.5f,	1.0f, 1.0f, 1.0f//点H 7


	};

	unsigned int indices[] = {
		/*上面ABC,BCD*/
		0,1,2,
		1,2,3,

		/*下面EFG,FGH*/
		4,5,6,
		5,6,7,
		/*左侧面ABF,AEF*/
		0,1,5,
		0,4,5,
		/*右侧面CDH,CGH*/
		2,3,7,
		2,6,7,
		/*前面ACG,AEG*/
		0,2,6,
		0,4,6,
		/*后面BFH,BDH*/
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
	glEnableVertexAttribArray(0);//位置函数，对应shader.vs中的aPos，6表示6个点。

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//颜色函数，对应shader.vs中的aColor，6表示6个点

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		ourShader.use();

		glm::mat4 transform;
		transform = glm::rotate(transform, 1 * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));//绕x，y，z轴逆时针旋转。OpenGL中逆时针为正方向

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);//一个面两个三角形，6个面12个三角形，一个三角形占3字节

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	return 0;
}