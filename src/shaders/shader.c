#include <shader.h>


#define INFO_LOG_SIZE 1024

unsigned int createShader(const char* pathToVertexShaderFile, const char* pathToFragmentShaderFile);
{
	// Read files
	char* vertexShaderSource, fragmentShaderSource;
	int   fileSize;
	FILE* file;

	file = open(pathToVertexShaderFile, "r");
	if(!file)
	{
		printf("%s%s", "ERROR::FILE::OPENING", pathToVertexShaderFile);
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file) + 1;
	fseek(file, 0, SEEK_SET);
	
	vertexShaderSource = (char*)malloc(fileSize * sizeof(char));
	fread(vertexShaderSource, fileSize, 1, file);
	vertexShaderSource[fileSize] = 0;


	file = open(pathToFragmentShaderFile, "r");
	if(!file)
	{
		printf("%s%s", "ERROR::FILE::OPENING", pathToFragmentShaderFile);
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file) + 1;
	fseek(file, 0, SEEK_SET);

	fragmentShaderSource = (char*)malloc(fileSize * sizeof(char));
	fread(fragmentShaderSource, fileSize, 1, file);
	fragmentShaderSource[fileSize] = 0;
	
	fclose(file);

	// Compile shaders
	unsigned int vertexShader, fragmentShader, shaderProgram;

	// vertex
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	checkCompileErrors(vertexShader, "VERTEX");

	
	// fragment
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	checkCompileErrors(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram)

	checkCompileErrors(shaderProgram, "PROGRAM");	


	// Delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	free(vertexShaderSource);	
	free(fragmentShaderSource);
	free(file);

	return shaderProgram;
}

void shaderUse(Shader shader);
{
	glUseProgram(ID);
}

void setBool(Shader shader, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader.ID, name), value);
}

void setInt(Shader shader, const char* name, int value);
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

