#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct Shader
{
	unsigned int ID;
} Shader;

unsigned int createShader(const char* pathToVertexShaderFile, const char* pathToFragmentShaderFile);

void shaderUse(unsigned int shaderId);

void setBool(Shader shader, const char* name, int value);

void setInt(Shader shader, const char* name, int value);

void setFloat(Shader shader, const char* name, float value);

void checkCompileErrors(unsigned int shader, const char* type);

#endif
