#include "stdafx.h"
#include "CEngine.h"
#include "CWindow.h"
#include "ShaderUtils.h"
#include "CObjLoader.h"

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
	CShader Shader1; Shader1.Load("shaders/vert.glsl", "shaders/frag.glsl");
	CShader Shader2; Shader2.Load("shaders/vert.glsl", "shaders/frag2.glsl");
	CTexture Texture;
	Texture.Load("rsc/terrain.jpg");
	CTexture Terrain;
	Terrain.Load("rsc/terrain.bmp");
	m_Shaders.push_back(Shader1);
	m_Shaders.push_back(Shader2);

	CGLObject* Object = CObjLoader::Load("rsc/terrain.obj");
	//CGLObject* Object = new CGLObject();
	//Object->SetVertices({ {0.f,0.f,0.f},{1.f,0.f,0.f},{1.f,1.f,0.f} });
	//Object->SetIndices({0,1,2});
	Object->SetProgram(Shader1.Program);
	Object->SetTexture(Texture);
	Object->Prepare();

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
	Object->SetModel(model);

	m_Objects.push_back(Object);
	m_Terrain = Object;

	glEnable(GL_DEPTH_TEST);
	glfwGetCursorPos(m_Window->GetWindow(), &m_LastX, &m_LastY);
}

void CEngine::Start()
{
	m_Window->Show(this);
}

void CEngine::OnDrow()
{
	double currentFrame = glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DoMovement();

	// ќбратите внимание, что мы смещаем сцену в направлении обратном тому, в котором мы хотим переместитьс€
	

	glm::mat4 View = m_Camera.GetView();
	glm::mat4 Projection = glm::perspective(glm::radians(m_FOV), 800.f / 600.f, 0.1f, 10000.0f);

	for (CGLObject* Object : m_Objects)
	{
		Object->Draw(View, Projection);
	}
}

void CEngine::OnKey(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		m_Keys[key] = true;
	else if (action == GLFW_RELEASE)
		m_Keys[key] = false;
}

void CEngine::OnMouseMove(double xpos, double ypos)
{
	double xoffset = xpos - m_LastX;
	double yoffset = m_LastY - ypos; // ќбратный пор€док вычитани€ потому что оконные Y-координаты возрастают с верху вниз 
	m_LastX = xpos;
	m_LastY = ypos;

	const double sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_Camera.Rotate(static_cast<GLfloat>(xoffset), static_cast<GLfloat>(yoffset));
}

void CEngine::OnScroll(double xoffset, double yoffset)
{
	if (m_FOV >= 1.0f && m_FOV <= 45.0f)
		m_FOV -= static_cast<GLfloat>(yoffset);
	m_FOV = std::max(m_FOV, 1.0f);
	m_FOV = std::min(m_FOV, 45.0f);
}

void CEngine::DoMovement()
{
	if (m_Keys[GLFW_KEY_W])
		m_Camera.Move(EDirection::Forward, static_cast<GLfloat>(m_DeltaTime));
	if (m_Keys[GLFW_KEY_S])
		m_Camera.Move(EDirection::Back , static_cast<GLfloat>(m_DeltaTime));
	if (m_Keys[GLFW_KEY_A])
		m_Camera.Move(EDirection::Left, static_cast<GLfloat>(m_DeltaTime));
	if (m_Keys[GLFW_KEY_D])
		m_Camera.Move(EDirection::Right, static_cast<GLfloat>(m_DeltaTime));
}
