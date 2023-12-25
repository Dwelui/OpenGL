/*
TODO:
1. Add some way to go around using absolute path to locate shaders
2. Refactor error logging
3. checkCompileErrors prints bullshit string
4. Refactor fuction names so that it is clear that this class is responsible for them
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct Shader
{
	unsigned int ID;
} Shader;

unsigned int createShader(const char* pathToVertexShaderFile, const char* pathToFragmentShaderFile);

void shaderUse(unsigned int shaderId);

void setBool(unsigned int shaderId, const char* name, int value);

void setInt(unsigned int shaderId, const char* name, int value);

void setFloat(unsigned int shaderId, const char* name, float value);

void checkCompileErrors(unsigned int shader, const char* type);

#endif
