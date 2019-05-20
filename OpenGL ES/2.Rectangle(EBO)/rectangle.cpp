#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);//�ص�����
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);//�������Esc��������˳���
	}
}


/*----------------------------------���붥����ɫ��-------------------------------------*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"//���������ݵ��뵽vec3��aPos���shader�е��������
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"//ǰ3�������ֱ��Ӧ��������4������͸�ӳ�����
"}\0";
/*----------------------------------���붥����ɫ��-------------------------------------*/


/*----------------------------------����Ƭ����ɫ��-------------------------------------*/

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"//��out�ؼ�����������������ΪFragColor
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//���ĸ�������ʾ���������ɫ
	//�ĸ�������Ӧ�죬�̣�����ǿ�ȣ��Լ�͸���ȡ�
	"}\n\0";
/*----------------------------------����Ƭ����ɫ��-------------------------------------*/

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/*----------------------------------�������ڶ���-------------------------------------*/
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "���ڴ�ʧ�ܣ�" << std::endl;
		glfwTerminate();//�رմ���
		system("pause");
		return -1;
	}

	glfwMakeContextCurrent(window);
	/*----------------------------------�������ڶ���-------------------------------------*/


	/*----------------------------------�ӿ�-------------------------------------*/
	//ǰ�����������ƴ������½�λ�ã��������������ƴ��ڴ�С

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//�����ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���á�
	//��������Ĥ(Retina)��ʾ����width��height�������Ա�ԭ����ֵ����һ�㡣

	/*----------------------------------�ӿ�-------------------------------------*/







	/*----------------------------------��������-------------------------------------*/
	float vertices[] =
	{
		//��һ��������
		0.5f,0.5f,0.0f,//���Ͻ�
		0.5f,-0.5f,0.0f,//���½�
		-0.5f, 0.5f,0.0f,//���Ͻ�
		-0.5f,-0.5f,0.0f,//���½�
	};

	unsigned int indices[] =
	{
		0,1,3,//��һ��������
		3,2,0//�ڶ���������
	};

	/*----------------------------------��������-------------------------------------*/






	/*----------------------------------GLAD����ָ�����-------------------------------------*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "����GLADʧ�ܣ�" << std::endl;
		system("pause");
		return -1;
	}
	/*----------------------------------GLAD����ָ�����-------------------------------------*/



	/*----------------------------------������ɫ��-------------------------------------*/


	unsigned int vertexShader;//������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*---------�ж��Ƿ񴴽��ɹ�-------*/
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "��ɫ������ʧ��" << infoLog << std::endl;
	}
	/*---------�ж��Ƿ񴴽��ɹ�-------*/

	/*----------------------------------������ɫ��-------------------------------------*/



	/*----------------------------------Ƭ����ɫ��-------------------------------------*/
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*----------------------------------Ƭ����ɫ��-------------------------------------*/

	/*----------------------------------��ɫ������-------------------------------------*/
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//��TM����֪���ˣ�ǰ����ôһ��ѣ�����Ϊ����һ��������������������������������

	/*-----�ж��Ƿ񴴽��ɹ�-----*/
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "���򴴽�ʧ��" << infoLog << std::endl;
	}
	/*-----�ж��Ƿ񴴽��ɹ�-----*/



	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);//����Ҫ�����ˣ�����ɾ����
	/*----------------------------------��ɫ������-------------------------------------*/

	/*-------------------------------������������-------------------------------*/
	unsigned int VBO;//�������㻺�����
	glGenBuffers(1, &VBO);//��VBO

	unsigned int VAO;//���������������
	glGenVertexArrays(1, &VAO);//��VAO

	unsigned int EBO;//���������������
	glGenBuffers(1, &EBO);//��EBO

	glBindVertexArray(VAO);//�Ѷ������鸴�Ƶ������й�OpenGLʹ��

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���ö�������ָ��

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//������������ָ��
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	


	/*-------------------------------������������-------------------------------*/





	/*----------------------------------����׼��-------------------------------------*/

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//�������Esc��������˳���

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�ص�Ĭ��ģʽ
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//��ͼ
		glUseProgram(shaderProgram);//����������
		glfwSwapBuffers(window);
		//�����ύ����ɫ���壬������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents();//�����û�д���ʲô�¼�������������롢����ƶ��ȣ�
	}



	/*----------------------------------����׼��-------------------------------------*/

	glfwTerminate();//����
	return 0;
}