#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <cglm/cglm.h>

#include <shader/shader.h>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float opacity = 0.5f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Transformations", NULL, NULL);
	if(window == NULL)
	{
		printf("%s", "Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("%s", "Failed to initialize GLAD");
		return -1;	
	}

	// GLMC
	//vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};
	/*
	mat4 trans = GLM_MAT4_IDENTITY_INIT;
	
	glm_rotated(trans, (GLM_PI / 180.0f) * 45.0f, (vec3){0.0f, 0.0f, 1.0f});
	
	trans[3][0] = 0.5f;
	trans[3][1] = 0.5f;
	trans[3][2] = 0.5f;
	*/
/*
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) {
			printf("%1.1ff, ", trans[i][j]);	
		}
	printf("\n");
*/
	//glm_mat4_transpose(trans);
	/*
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			printf("%f ", trans[i][j]);
		printf("\n");
	}
	*/
	//glm_mat4_mul(trans, vec, trans); //wth
	//glm_mat4_mulv(trans, vec, vec);
	// printf("%f %f %f %f %s", vec[0], vec[1], vec[2], vec[3], "\n");

	// Create shaders
	unsigned int myShader;
	myShader = createShader("C:/Users/manta/Desktop/Projects/Coding/C/OpenGL/src/transformations/shader.vs", "C:/Users/manta/Desktop/Projects/Coding/C/OpenGL/src/transformations/shader.fs");

	float vertices[] = {
		 // positions          // colors           // texture coords
	     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	
	unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
	
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// Load textures
	stbi_set_flip_vertically_on_load(true);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("C:/Users/manta/Desktop/Projects/Coding/C/OpenGL/assets/container.jpg", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("%s", "Failed to load texture\n");
	}

	stbi_image_free(data);


	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("C:/Users/manta/Desktop/Projects/Coding/C/OpenGL/assets/awesomeface.png", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("%s", "Failed to load texture\n");
	}

	stbi_image_free(data);

	shaderUse(myShader);
	setInt(myShader, "texture1", 0);
	setInt(myShader, "texture2", 1);

	// Convert float(*)[] to const float *
	
/*
	float* transv = (float *)calloc(16, sizeof(float));

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) {
			transv[4 * i + j] = trans[i][j];
		}
*/
/*
	printf("\n");
	for(int i = 0; i < 16; i++)
		printf("%1.1ff, ", transv[i]);
*/
/*
	unsigned int transformLoc = glGetUniformLocation(myShader, "transform");	
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transv);
*/
	
	mat4 trans = GLM_MAT4_IDENTITY_INIT;

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);		





	
		glm_rotated(trans, (GLM_PI / 180.0f) * 0.05f, (vec3){0.0f, 0.0f, 1.0f});
	
		trans[3][0] = 0.5f;
		trans[3][1] = 0.5f;
		trans[3][2] = 0.5f;


		float* transv = (float *)calloc(16, sizeof(float));

		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				transv[4 * i + j] = trans[i][j];

		unsigned int transformLoc = glGetUniformLocation(myShader, "transform");	
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transv);

				
		setFloat(myShader, "opacity", opacity);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		shaderUse(myShader);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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

	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		opacity -= 0.001;
	}

	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		opacity += 0.001;
	}

}
