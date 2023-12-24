#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<stdio.h>
#include<stdbool.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	
	"}\0";

const char *fragmentShaderSource_1 =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const char *fragmentShaderSource_2 =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("%s", "Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("%s", "Failed to initialize GLAD");		
		return -1;
	}

	// SHADERS
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("%s%s", "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}


	unsigned int fragmentShader_1, fragmentShader_2;
	fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader_1, 1, &fragmentShaderSource_1, NULL);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_1);
	glCompileShader(fragmentShader_2);

	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);
		printf("%s%s", "ERROR::SHADER::FRAGMENT_1::COMPILATION_FAILED\n", infoLog);
	}

	glGetShaderiv(fragmentShader_2, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLog);
		printf("%s%s", "ERROR::SHADER::FRAGMENT_2::COMPILATION_FAILED\n", infoLog);
	}


	unsigned int shaderProgram_1, shaderProgram_2;
	shaderProgram_1 = glCreateProgram();
	shaderProgram_2 = glCreateProgram();

	glAttachShader(shaderProgram_1, vertexShader);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);

	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);


	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shaderProgram_1, 512, NULL, infoLog);
		printf("%s%s", "ERROR::SHADER::PROGRAM_1::LINK_FAILED\n", infoLog);
	}

	glGetProgramiv(shaderProgram_2, GL_LINK_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shaderProgram_2, 512, NULL, infoLog);
		printf("%s%s", "ERROR::SHADER::PROGRAM_2::LINK_FAILED\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_1);
	glDeleteShader(fragmentShader_2);

/*
	float vertices[] = {
	     0.5f,  0.5f, 0.0f,  // top right
	     0.5f, -0.5f, 0.0f,  // bottom right
	    -0.5f, -0.5f, 0.0f,  // bottom left
	    -0.5f,  0.5f, 0.0f   // top left 
	};
*/
/*
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
*/


float vertices_1[] = {
	// first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
}; 

float vertices_2[] = {
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram_1);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram_2);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);
	glDeleteProgram(shaderProgram_1);
	glDeleteProgram(shaderProgram_2);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
