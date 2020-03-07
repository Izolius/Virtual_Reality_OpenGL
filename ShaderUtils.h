#pragma once
#include <string>

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragmet = GL_FRAGMENT_SHADER
};
class ShaderUtils
{
public:
	static GLuint LoadShader(ShaderType type, const std::string& filename);
	static GLuint CreateProgram(const std::initializer_list<GLuint>& Shaders);
};

class CShader
{
public:
	GLuint Program = -1;

	void Load(const std::string& Vertex, const std::string& Fragment);
	void Use();
};

