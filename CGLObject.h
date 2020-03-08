#pragma once
#include <vector>
#include "CUniformParam.h"


class CGLObject
{
	GLuint VAO, m_Propgram;
	GLuint m_VertexBuffer, m_UVBuffer, m_NormalBuffer;
	GLuint m_VertexElementBuffer, m_UVElementBuffer, m_NormalElementBuffer;
	CTexture m_Texture;
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec2> m_UVs;
	std::vector<glm::vec3> m_Normales;
	std::vector<GLuint> m_VertexIndices, m_UVIndices, m_NormalIndices;
	glm::mat4 m_Model;
	std::vector<CUniformParam*> m_UniformParams;
private:
	bool HasTexture() const;
public:
	CGLObject();
	~CGLObject();
	void SetProgram(GLuint Program);
	void Draw(const glm::mat4& View, const glm::mat4& Projection);
	void SetVertices(const std::vector<glm::vec3>& Vertices);
	void SetIndices(const std::vector<GLuint>& Indices);
	void SetUVs(const std::vector<glm::vec2>& UVs);
	void SetTexture(CTexture Texture);
	void SetModel(const glm::mat4& Model);
	void AddUniformParam(CUniformParam* Param);
	void Prepare();
};

