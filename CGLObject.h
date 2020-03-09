#pragma once
#include <vector>
#include "CUniformParam.h"


class CGLObject
{
protected:
	GLuint VAO, m_Propgram;
	GLuint m_VertexBuffer;
	GLuint m_VertexElementBuffer;
	std::vector<glm::vec3> m_Vertices;
	
	std::vector<GLuint> m_VertexIndices;
	glm::mat4 m_Model;
	std::vector<CUniformParam*> m_UniformParams;
public:
	CGLObject();
	~CGLObject();
	void SetProgram(GLuint Program);
	virtual void Draw(const std::vector<CUniformParam*>& Params);
	void SetVertices(const std::vector<glm::vec3>& Vertices);
	void SetIndices(const std::vector<GLuint>& Indices);
	
	void SetModel(const glm::mat4& Model);
	void AddUniformParam(CUniformParam* Param);
	virtual void Prepare();
};

class CGlMesh : public CGLObject
{
	GLuint m_UVBuffer, m_NormalBuffer;
	CTexture m_Texture;
	std::vector<glm::vec2> m_UVs;
	std::vector<glm::vec3> m_Normales;

	bool HasTexture() const;
public:
	virtual void Draw(const std::vector<CUniformParam*>& Params);
	void SetUVs(const std::vector<glm::vec2>& UVs);
	void SetTexture(CTexture Texture);
	void SetNormales(const std::vector<glm::vec3>& Normales);
	virtual void Prepare();
};

