#include <stdlib.h>
#include <stdio.h>

#include <shader.h>

#define INFO_LOG_SIZE 1024

unsigned int createShader(const char* pathToVertexShaderFile, const char* pathToFragmentShaderFile)
{
	// Read files
	char* vertexShaderSource;
	char* fragmentShaderSource;
	int   fileSize;
	FILE* file;

	file = fopen(pathToVertexShaderFile, "r");
	if(!file)
	{
		printf("%s%s%s", "ERROR::FILE::OPENING\nPATH: ", pathToVertexShaderFile, "\n");
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	vertexShaderSource = malloc(fileSize * sizeof(char));
	fread(vertexShaderSource, fileSize, 1, file);
	vertexShaderSource[fileSize] = 0;


	file = fopen(pathToFragmentShaderFile, "r");
	if(!file)
	{
		printf("%s%s%s", "ERROR::FILE::OPENING\nPATH: ", pathToFragmentShaderFile, "\n");
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	fragmentShaderSource = malloc(fileSize * sizeof(char));
	fread(fragmentShaderSource, fileSize, 1, file);
	fragmentShaderSource[fileSize] = 0;
	
	fclose(file);

	// Compile shaders
	unsigned int vertexShader, fragmentShader, shaderProgram;
	const char* vertexShaderCode = vertexShaderSource; 
	const char* fragmentShaderCode = fragmentShaderSource;

	// vertex
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	
	checkCompileErrors(vertexShader, "VERTEX");

	
	// fragment
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	
	checkCompileErrors(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkCompileErrors(shaderProgram, "PROGRAM");	


	// Delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	free(vertexShaderSource);	
	free(fragmentShaderSource);
	free(file);

	return shaderProgram;
}

void shaderUse(unsigned int shaderId)
{
	glUseProgram(shaderId);
}

void setBool(Shader shader, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader.ID, name), value);
}

void setInt(Shader shader, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader.ID, name), value);	
}

void setFloat(Shader shader, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader.ID, name), value);
}

void checkCompileErrors(unsigned int shader, const char* type)
{
	int  success;
	char infoLog[INFO_LOG_SIZE];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		
		if(!success)
		{
			glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
			printf("%s%s%s", "ERROR::SHADER::", type, "::COMPILATION_ERROR\n");
			printf("%s%s", infoLog, "\n-- ---------------------------------------------- --\n");	
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		
		if(!success)
		{
			glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
			printf("%s%s%s", "ERROR::SHADER::", type, "::COMPILATION_ERROR\n");
			printf("%s%s", infoLog, "\n-- ---------------------------------------------- --\n");	
		}
	}
}

