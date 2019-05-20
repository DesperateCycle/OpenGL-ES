#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);//回调函数
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);//如果按下Esc，则程序退出。
	}
}


/*----------------------------------编译顶点着色器-------------------------------------*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"//把坐标数据导入到vec3，aPos这个shader中的坐标变量
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"//前3个参数分别对应向量，第4个用在透视除法上
"}\0";
/*----------------------------------编译顶点着色器-------------------------------------*/


/*----------------------------------编译片段着色器-------------------------------------*/

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"//用out关键字声明变量，命名为FragColor
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//这四个变量表示的是输出颜色
	//四个参数对应红，绿，蓝的强度，以及透明度。
	"}\n\0";
/*----------------------------------编译片段着色器-------------------------------------*/

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/*----------------------------------创建窗口对象-------------------------------------*/
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "窗口打开失败！" << std::endl;
		glfwTerminate();//关闭窗口
		system("pause");
		return -1;
	}

	glfwMakeContextCurrent(window);
	/*----------------------------------创建窗口对象-------------------------------------*/


	/*----------------------------------视口-------------------------------------*/
	//前两个参数控制窗口左下角位置，后两个参数控制窗口大小

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//当窗口被第一次显示的时候framebuffer_size_callback也会被调用。
	//对于视网膜(Retina)显示屏，width和height都会明显比原输入值更高一点。

	/*----------------------------------视口-------------------------------------*/







	/*----------------------------------顶点输入-------------------------------------*/
	float vertices[] =
	{
		//第一个三角形
		0.5f,0.5f,0.0f,//右上角
		0.5f,-0.5f,0.0f,//右下角
		-0.5f, 0.5f,0.0f,//左上角
		-0.5f,-0.5f,0.0f,//左下角
	};

	unsigned int indices[] =
	{
		0,1,3,//第一个三角形
		3,2,0//第二个三角形
	};

	/*----------------------------------顶点输入-------------------------------------*/






	/*----------------------------------GLAD管理指针操作-------------------------------------*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "创建GLAD失败！" << std::endl;
		system("pause");
		return -1;
	}
	/*----------------------------------GLAD管理指针操作-------------------------------------*/



	/*----------------------------------顶点着色器-------------------------------------*/


	unsigned int vertexShader;//创建着色器对象
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*---------判断是否创建成功-------*/
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "着色器创建失败" << infoLog << std::endl;
	}
	/*---------判断是否创建成功-------*/

	/*----------------------------------顶点着色器-------------------------------------*/



	/*----------------------------------片段着色器-------------------------------------*/
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*----------------------------------片段着色器-------------------------------------*/

	/*----------------------------------着色器程序-------------------------------------*/
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//我TM终于知道了，前面那么一大堆，就是为了这一步。。哈哈哈哈哈哈哈哈哈哈哈哈哈

	/*-----判断是否创建成功-----*/
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "程序创建失败" << infoLog << std::endl;
	}
	/*-----判断是否创建成功-----*/



	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);//不需要他们了，可以删除了
	/*----------------------------------着色器程序-------------------------------------*/

	/*-------------------------------解析顶点数据-------------------------------*/
	unsigned int VBO;//创建顶点缓冲对象
	glGenBuffers(1, &VBO);//绑定VBO

	unsigned int VAO;//创建顶点数组对象
	glGenVertexArrays(1, &VAO);//绑定VAO

	unsigned int EBO;//创建索引缓冲对象
	glGenBuffers(1, &EBO);//绑定EBO

	glBindVertexArray(VAO);//把顶点数组复制到缓冲中供OpenGL使用

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置顶点属性指针

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//设置索引属性指针
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	


	/*-------------------------------解析顶点数据-------------------------------*/





	/*----------------------------------引擎准备-------------------------------------*/

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//如果按下Esc，则程序退出。

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//回到默认模式
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//绘图
		glUseProgram(shaderProgram);//激活程序对象
		glfwSwapBuffers(window);
		//函数会交换颜色缓冲，它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
		glfwPollEvents();//检查有没有触发什么事件（比如键盘输入、鼠标移动等）
	}



	/*----------------------------------引擎准备-------------------------------------*/

	glfwTerminate();//结束
	return 0;
}