#include "stdafx.h"
#include "CEngine.h"
#include "CWindow.h"
#include "ShaderUtils.h"

CEngine::CEngine(CWindow* Window):
	m_Window(Window)
{
}

void CEngine::Prepare()
{
	CShader Shader1; Shader1.Load("vert.glsl", "frag.glsl");
	CShader Shader2; Shader2.Load("vert.glsl", "frag2.glsl");
	CTexture Texture;
	Texture.Load("texture.jpg");
	m_Shaders.push_back(Shader1);
	m_Shaders.push_back(Shader2);

	CGLObject* Triangle1=new CGLObject();
	Triangle1->SetVertices({
		// Позиции          // Цвета             // Текстурные координаты
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
		});
	Triangle1->SetIndices({ 0,1,3,1,2,3 });
	Triangle1->SetProgram(Shader1.Program);
	Triangle1->SetTexture(Texture);
	Triangle1->Prepare();
	m_Objects.push_back(Triangle1);
}

void CEngine::Start()
{
	m_Window->Show(this);
}

void CEngine::OnDrow()
{
	//// Обновляем цвет формы
	//m_Shaders[0].Use();
	//double timeValue = glfwGetTime();
	//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	//GLint vertexColorLocation = glGetUniformLocation(m_Shaders[0].Program, "ourColor");
	//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	for (CGLObject* Object : m_Objects)
	{
		Object->Draw();
	}
}
