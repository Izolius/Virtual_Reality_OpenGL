#include "stdafx.h"
#include "CUniformParam.h"

void CUniformParam_mat4::Set(GLuint Program)
{
	GLint Location = glGetUniformLocation(Program, Name.c_str());
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Value));
}

void CUniformParam_vec3::Set(GLuint Program)
{
	GLint Location = glGetUniformLocation(Program, Name.c_str());
	glUniform3f(Location, Value.x, Value.y, Value.z);
}
