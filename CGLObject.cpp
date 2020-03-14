#include "stdafx.h"
#include "CGLObject.h"
#include <algorithm>
#include <numeric>
using namespace std;

int s_UniqueColor = 0;
std::vector<glm::vec<4, unsigned char>> s_UniqueColors({
	glm::vec<4, unsigned char>({0,0,100,255}),
	glm::vec<4, unsigned char>({0,100,0,255}),
	glm::vec<4, unsigned char>({100,0,0,255}),
	glm::vec<4, unsigned char>({100,100,0,255}),
	glm::vec<4, unsigned char>({0,100,100,255}),
	glm::vec<4, unsigned char>({100,0,100,255}),
	glm::vec<4, unsigned char>({100,50,0,255}),
	glm::vec<4, unsigned char>({100,0,50,255}),
	});

CGLObject::CGLObject()
{
	m_UniqueColor = s_UniqueColors[s_UniqueColor++];
}

CGLObject::~CGLObject()
{
	glDeleteVertexArrays(1, &VAO);
}

glm::vec<4, unsigned char> CGLObject::GetUniqueColor() const
{
	return m_UniqueColor;
}

void CGLObject::SetProgram(GLuint Program)
{
	m_Propgram = Program;
}

GLuint CGLObject::GetProgram() const
{
	return m_Propgram;
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

glm::mat4 CGLObject::GetModel() const
{
	return m_Model;
}

void CGLObject::AddUniformParam(CUniformParam* Param)
{
	m_UniformParams.push_back(Param);
}

void CGLMesh::SetUVs(const std::vector<glm::vec2>& UVs)
{
	m_UVs = UVs;
}

void CGLMesh::SetTexture(CTexture Texture)
{
	m_Texture = Texture;
}

void CGLMesh::SetNormales(const std::vector<glm::vec3>& Normales)
{
	m_Normales = Normales;
}

bool CGLMesh::HasTexture() const
{
	return m_Texture.Texture != -1;
}

void CGLMesh::Draw(const std::vector<CUniformParam*>& Params)
{
	if (ObjectType == EObjectType::SkyBox)
		glDepthMask(GL_FALSE);
	glUseProgram(m_Propgram);

	if (HasTexture())
		if (m_Texture.Coords == 2)
			glBindTexture(GL_TEXTURE_2D, m_Texture.Texture);
		else
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture.Texture);

	GLint modelLoc = glGetUniformLocation(m_Propgram, "model");
	if (modelLoc != -1)
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

	if (ObjectType == EObjectType::SkyBox)
		glDepthMask(GL_TRUE);
}

void CGLMesh::Prepare()
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

float MAX_SIZE = 100, STEP_SIZE = 1;

void CGLTerrain::InitGrid()
{
	m_Vertices.resize(m_HeightMap.Width * m_HeightMap.Height);
	m_VertexIndices.reserve(m_HeightMap.Width * m_HeightMap.Height * 6);
	vector<vector<GLuint>> Indices(m_HeightMap.Height, vector<GLuint>(m_HeightMap.Width));
	int Index = 0;
	float HalfWidth = m_HeightMap.Width / 2.0, HalfHeight = m_HeightMap.Height / 2.0;
	for (int z = 0; z < m_HeightMap.Height; z += STEP_SIZE)
	{
		for (int x = 0; x < m_HeightMap.Width; x += STEP_SIZE)
		{
			m_Vertices[z * m_HeightMap.Width + x] =
				glm::vec3((x - HalfWidth) / HalfWidth, GetHeight(x, z), (z - HalfHeight) / HalfHeight);
			Indices[z][x] = Index++;
		}
	}

	

	for (int x = 0; x < m_HeightMap.Width - STEP_SIZE; x += STEP_SIZE)
	{
		for (int z = 0; z < m_HeightMap.Height - STEP_SIZE; z += STEP_SIZE)
		{
			m_VertexIndices.insert(m_VertexIndices.end(),
				{ Indices[z][x], Indices[z][x + STEP_SIZE],Indices[z + STEP_SIZE][x] });
			m_VertexIndices.insert(m_VertexIndices.end(),
				{ Indices[z][x + STEP_SIZE],Indices[z + STEP_SIZE][x],Indices[z + STEP_SIZE][x + STEP_SIZE] });
		}
	}

	m_UVs.resize(m_HeightMap.Width * m_HeightMap.Height);
	float UV_STEP = STEP_SIZE / m_HeightMap.Width;
	float u = 0, v = 0;
	for (int z = 0; z < m_HeightMap.Height; z += STEP_SIZE, u += UV_STEP)
	{
		for (int x = 0; x < m_HeightMap.Width; x += STEP_SIZE, v += UV_STEP)
		{
			m_UVs[z * m_HeightMap.Width + x] = glm::vec2(1 - u, v);
		}
	}

	m_Normales.resize(m_HeightMap.Width * m_HeightMap.Height);

	for (int z = 0; z < m_HeightMap.Height; z += STEP_SIZE)
	{
		for (int x = 0; x < m_HeightMap.Width; x += STEP_SIZE)
		{
			vector<glm::vec3> Normales;
			if (z > 0)
				Normales.push_back(m_Vertices[(z - 1) * m_HeightMap.Width + x]);
			if (z < m_HeightMap.Height - 1)
				Normales.push_back(m_Vertices[(z + 1) * m_HeightMap.Width + x]);
			if (x > 0)
				Normales.push_back(m_Vertices[z * m_HeightMap.Width + x - 1]);
			if (x < m_HeightMap.Width - 1)
				Normales.push_back(m_Vertices[z * m_HeightMap.Width + x + 1]);

			for (auto& Neighbor : Normales)
				Neighbor = m_Vertices[z * m_HeightMap.Width + x] - Neighbor;

			for (size_t i = 0; i < Normales.size(); i++)
			{
				Normales[i] = glm::cross(Normales[i], Normales[(i + 1) % Normales.size()]);
			}
			m_Normales[z * m_HeightMap.Width + x] =
				std::accumulate(Normales.begin(), Normales.end(), glm::vec3(0.f, 0.f, 0.f)) / (float)Normales.size();
		}
	}
	
}

float CGLTerrain::GetHeight(int x, int z)
{
	float Height = m_HeightMap.GetHeight(x, m_HeightMap.Width - z - 1);
	return Height / 255.0f;
}

void CGLTerrain::Prepare()
{
	InitGrid();
	CGLMesh::Prepare();
}

void CGLTerrain::SetHeightMap(const CHeightMap& HeightMap)
{
	m_HeightMap = HeightMap;
}
