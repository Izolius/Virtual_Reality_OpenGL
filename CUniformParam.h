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
	const glm::mat4& Value;
	virtual void Set(GLuint Program) override;
	CUniformParam_mat4(const glm::mat4& Value, const std::string& Name);
};

class CUniformParam_vec3 : public CUniformParam
{
public:
	const glm::vec3& Value;
	virtual void Set(GLuint Program) override;
	CUniformParam_vec3(const glm::vec3& Value, const std::string& Name);
};

class CUniformParam_vec4 : public CUniformParam
{
public:
	const glm::vec4& Value;
	virtual void Set(GLuint Program) override;
	CUniformParam_vec4(const glm::vec4& Value, const std::string& Name);
};
