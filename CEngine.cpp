#include "stdafx.h"
#include "CEngine.h"
#include "CWindow.h"
#include "ShaderUtils.h"

CEngine::CEngine(CWindow* Window):
	m_Window(Window)
{
}

CEngine::~CEngine()
{
	for (CTexture& t : m_Textures)
		glDeleteTextures(1, &t.Texture);
	for (CShader& s : m_Shaders)
		glDeleteProgram(s.Program);
}

void CEngine::Prepare()
{
	CShader Shader1; Shader1.Load("vert.glsl", "frag.glsl");
	CShader Shader2; Shader2.Load("vert.glsl", "frag2.glsl");
	CTexture Texture;
	Texture.Load("texture2.jpg");
	m_Shaders.push_back(Shader1);
	m_Shaders.push_back(Shader2);

	glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (int i = 0; i < 10; i++)
	{
		CGLObject* Object = new CGLObject();
		Object->SetVertices({
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			});
		//Triangle1->SetIndices({ 0,1,3,1,2,3 });
		Object->SetProgram(Shader1.Program);
		Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		Object->SetModel(model);

		m_Objects.push_back(Object);
	}

	glEnable(GL_DEPTH_TEST);
	m_View = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));
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

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Обратите внимание, что мы смещаем сцену в направлении обратном тому, в котором мы хотим переместиться
	

	m_Projection = glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 10000.0f);

	for (CGLObject* Object : m_Objects)
	{
		Object->Draw(m_View, m_Projection);
	}
}

void CEngine::OnKey(int key, int scancode, int action, int mode)
{
	constexpr float SHIFT = 0.1;
	constexpr float ANGLE = 5;
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_View = glm::rotate(m_View, -glm::radians(ANGLE), {0.f,1.f,0.f});
	}
	else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_View = glm::rotate(m_View, glm::radians(ANGLE), { 0.f,1.f,0.f });
	}
	else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_View = glm::translate(m_View, { 0.f,0.f,SHIFT });
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_View = glm::translate(m_View, { 0.f,0.f,-SHIFT });
	}
}
