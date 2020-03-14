#include "stdafx.h"
#include "CUniformParam.h"

void CUniformParam_mat4::Set(GLuint Program)
{
	GLint Location = glGetUniformLocation(Program, Name.c_str());
	if (Location != -1)
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Value));
}

CUniformParam_mat4::CUniformParam_mat4(const glm::mat4& Value, const std::string& Name):
	Value(Value)
{
	this->Name = Name;
}

void CUniformParam_vec3::Set(GLuint Program)
{
	GLint Location = glGetUniformLocation(Program, Name.c_str());
	if (Location != -1)
		glUniform3f(Location, Value.x, Value.y, Value.z);
}

CUniformParam_vec3::CUniformParam_vec3(const glm::vec3& Value, const std::string& Name) :
	Value(Value)
{
	this->Name = Name;
}

void CUniformParam_vec4::Set(GLuint Program)
{
	GLint Location = glGetUniformLocation(Program, Name.c_str());
	if (Location != -1)
		glUniform4f(Location, Value.r, Value.g, Value.b, Value.a);
}

CUniformParam_vec4::CUniformParam_vec4(const glm::vec4& Value, const std::string& Name) :
	Value(Value)
{
	this->Name = Name;
}
