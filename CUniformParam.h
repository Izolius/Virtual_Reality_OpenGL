#pragma once

class CUniformParam
{
public:
	std::string Name;
	virtual void Set(GLuint Program) = 0;
};

class CUniformParam_mat4 : public CUniformParam
{
public:
	glm::mat4 Value;
	virtual void Set(GLuint Program) override;
};

class CUniformParam_vec3 : public CUniformParam
{
public:
	glm::vec3 Value;
	virtual void Set(GLuint Program) override;
};

