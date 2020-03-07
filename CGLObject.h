#pragma once
#include <vector>
class CGLObject
{
	GLuint VBO, VAO, EBO, m_Propgram;
	CTexture m_Texture;
	std::vector<GLfloat> m_Vertices;
	std::vector<GLuint> m_Indices;
	glm::mat4 m_Model;
private:
	bool HasTexture() const;
public:
	CGLObject();
	~CGLObject();
	void SetProgram(GLuint Program);
	void Draw(const glm::mat4& View, const glm::mat4& Projection);
	void SetVertices(const std::vector<GLfloat>& Vertices);
	void SetIndices(const std::vector<GLuint>& Indices);
	void SetTexture(CTexture Texture);
	void SetModel(const glm::mat4& Model);
	void Prepare();
};

