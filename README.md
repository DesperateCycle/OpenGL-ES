编译环境是64位的VS2019。
使用源代码之前需要配好OpenGL ES（GLFW/GLAD等等）的环境。

从第3项(3.Cube)开始文件有以下变化：
1.需配好OpenGL相关的线性代数库（glm等）的环境。


2.前两项中的顶点着色器和片元着色器分别封装成了shader.vs,shader.fs。使用方法是在Shader创建时引用文件。
Shader ourShader("shader.vs", "/shader.fs");

渲染的时候需要用到以下函数：
例如：glEnableVertexAttribArray(0);//对应shader.vs中的layout (location = 0) in vec3 aPos; 
例如：glEnableVertexAttribArray(1);//对应layout (location = 1) in vec3 aColor; 


3.前两项中的program封装成了.h文件，使用方法是创建一个Shader类型的对象。然后在渲染循环中，对象需要引用use()方法。
ourShader.use();
