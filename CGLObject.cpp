#include "stdafx.h"
#include "CGLObject.h"
using namespace std;

CGLObject::CGLObject()
{
	
}

CGLObject::~CGLObject()
{
	glDeleteVertexArrays(1, &VAO);
}

void CGLObject::SetProgram(GLuint Program)
{
	m_Propgram = Program;
}

void CGLObject::Draw(const std::vector<CUniformParam*>& Params)
{
	glUseProgram(m_Propgram);

	GLint modelLoc = glGetUniformLocation(m_Propgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));

	for (CUniformParam* Param : m_UniformParams)
		Param->Set(m_Propgram);

	for (CUniformParam* Param : Params)
		Param->Set(m_Propgram);

	glBindVertexArray(VAO);
	if (m_VertexIndices.size())
		glDrawElements(GL_TRIANGLES, m_VertexIndices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void CGLObject::Prepare()
{
	GLuint Layout = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &m_VertexBuffer);
	if (m_VertexIndices.size())
		glGenBuffers(1, &m_VertexElementBuffer);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(Layout++);

	if (m_VertexIndices.size())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_VertexIndices.size(), m_VertexIndices.data(), GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CGLObject::SetVertices(const std::vector<glm::vec3>& Vertices)
{
	m_Vertices = Vertices;
}

void CGLObject::SetIndices(const std::vector<GLuint>& Indices)
{
	m_VertexIndices = Indices;
}

void CGLObject::SetModel(const glm::mat4& Model)
{
	m_Model = Model;
}

void CGLObject::AddUniformParam(CUniformParam* Param)
{
	m_UniformParams.push_back(Param);
}

void CGlMesh::SetUVs(const std::vector<glm::vec2>& UVs)
{
	m_UVs = UVs;
}

void CGlMesh::SetTexture(CTexture Texture)
{
	m_Texture = Texture;
}

void CGlMesh::SetNormales(const std::vector<glm::vec3>& Normales)
{
	m_Normales = Normales;
}

bool CGlMesh::HasTexture() const
{
	return m_Texture.Texture != -1;
}

void CGlMesh::Draw(const std::vector<CUniformParam*>& Params)
{
	glUseProgram(m_Propgram);

	if (HasTexture())
		glBindTexture(GL_TEXTURE_2D, m_Texture.Texture);

	GLint modelLoc = glGetUniformLocation(m_Propgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));

	for (CUniformParam* Param : m_UniformParams)
		Param->Set(m_Propgram);

	for (CUniformParam* Param : Params)
		Param->Set(m_Propgram);

	glBindVertexArray(VAO);
	if (m_VertexIndices.size())
		glDrawElements(GL_TRIANGLES, m_VertexIndices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void CGlMesh::Prepare()
{
	if (m_Vertices.size() == 0)
		throw exception("No Vertices");
	//if (m_Indices.size() == 0)
	//	throw exception("No Indices");

	GLuint Layout = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &m_VertexBuffer);
	if (m_VertexIndices.size())
		glGenBuffers(1, &m_VertexElementBuffer);
	if (m_UVs.size())
		glGenBuffers(1, &m_UVBuffer);
	if (m_Normales.size())
		glGenBuffers(1, &m_NormalBuffer);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(Layout++);

	if (m_VertexIndices.size())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_VertexIndices.size(), m_VertexIndices.data(), GL_STATIC_DRAW);
	}

	if (m_UVs.size() && HasTexture())
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * m_UVs.size(), m_UVs.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(Layout, m_Texture.Coords, GL_FLOAT, GL_FALSE, m_Texture.Coords * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(Layout++);
	}

	if (m_Normales.size())
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_Normales.size(), m_Normales.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(Layout++);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
