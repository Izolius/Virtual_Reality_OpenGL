#pragma once
#include <vector>
#include "CTexture.h"
class CGLObject
{
	GLuint VBO, VAO, EBO, m_Propgram;
	CTexture m_Texture;
	std::vector<GLfloat> m_Vertices;
	std::vector<GLuint> m_Indices;
private:
	bool HasTexture() const;
public:
	CGLObject();
	~CGLObject();
	void SetProgram(GLuint Program);
	void Draw();
	void SetVertices(const std::vector<GLfloat>& Vertices);
	void SetIndices(const std::vector<GLuint>& Indices);
	void SetTexture(CTexture Texture);
	void Prepare();
};

