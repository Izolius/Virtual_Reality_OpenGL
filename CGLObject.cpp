#include "stdafx.h"
#include "CGLObject.h"
using namespace std;

bool CGLObject::HasTexture() const
{
	return m_Texture.Texture != -1;
}

CGLObject::CGLObject()
{
	
}

CGLObject::~CGLObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void CGLObject::SetProgram(GLuint Program)
{
	m_Propgram = Program;
}

void CGLObject::Draw(const glm::mat4& View, const glm::mat4& Projection)
{
	if (HasTexture())
		glBindTexture(GL_TEXTURE_2D, m_Texture.Texture);
	glUseProgram(m_Propgram);

	GLint modelLoc = glGetUniformLocation(m_Propgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));

	modelLoc = glGetUniformLocation(m_Propgram, "view");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(View));

	modelLoc = glGetUniformLocation(m_Propgram, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Projection));

	glBindVertexArray(VAO);
	if (m_Indices.size())
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void CGLObject::SetVertices(const std::vector<GLfloat>& Vertices)
{
	m_Vertices = Vertices;
}

void CGLObject::SetIndices(const std::vector<GLuint>& Indices)
{
	m_Indices = Indices;
}

void CGLObject::SetTexture(CTexture Texture)
{
	m_Texture = Texture;
}

void CGLObject::SetModel(const glm::mat4& Model)
{
	m_Model = Model;
}

void CGLObject::Prepare()
{
	if (m_Vertices.size() == 0)
		throw exception("No Vertices");
	//if (m_Indices.size() == 0)
	//	throw exception("No Indices");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

	if (m_Indices.size())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);
	}

	GLsizei Stride = 3 * sizeof(GLfloat);
	if (HasTexture())
		Stride += m_Texture.Coords * sizeof(GLfloat);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Stride, nullptr);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Stride, (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	if (HasTexture())
	{
		glVertexAttribPointer(2, m_Texture.Coords, GL_FLOAT, GL_FALSE, Stride, (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
