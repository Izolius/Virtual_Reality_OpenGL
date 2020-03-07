#include "stdafx.h"
#include "ShaderUtils.h"
#include <fstream>
#include <iostream>
using namespace std;

GLuint ShaderUtils::LoadShader(ShaderType type, const std::string& filename)
{
	GLuint Shader = glCreateShader(static_cast<GLenum>(type));

	ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	const GLchar* vertexShaderSource = content.data();
	glShaderSource(Shader, 1, &vertexShaderSource, NULL);
	glCompileShader(Shader);

	// check for shader compile errors
	int success;
	char infoLog[1000];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 1000, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return Shader;
}

GLuint ShaderUtils::CreateProgram(const std::initializer_list<GLuint>& Shaders)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	for (GLuint Shader : Shaders)
	{
		glAttachShader(shaderProgram, Shader);
	}
	glLinkProgram(shaderProgram);
	for (GLuint Shader : Shaders)
	{
		glDeleteShader(Shader);
	}
	return shaderProgram;
}

void CShader::Load(const std::string& Vertex, const std::string& Fragment)
{
	Program = ShaderUtils::CreateProgram({
		ShaderUtils::LoadShader(ShaderType::Vertex, Vertex),
		ShaderUtils::LoadShader(ShaderType::Fragmet, Fragment) });
}

void CShader::Use()
{
	glUseProgram(Program);
}
