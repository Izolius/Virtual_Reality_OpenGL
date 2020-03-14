#include "stdafx.h"
#include "CEngine.h"
#include "CWindow.h"
#include "ShaderUtils.h"
#include "CObjLoader.h"
#include "CGLObject.h"
#include "CColorPicker.h"
#include <iostream>
using namespace std;

CEngine::CEngine(CWindow* Window):
	m_Window(Window), m_LightPos(3.0f, 2.0f, 2.0f)
{
	cout << "c - to switch cursor mode" << endl;
	cout << "p - to switch color pick drawinig mode" << endl;
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
	{
		CShader Shader; Shader.Load("shaders/vert_color_picking.glsl", "shaders/frag_color_picking.glsl");
		m_ColorPicker.reset(new CColorPicker(Shader.Program));
	}

	if (true)
	{
		CCubeTexture Texture;
		Texture.Load({
			"rsc/skybox/right.jpg",
			"rsc/skybox/left.jpg",
			"rsc/skybox/top.jpg",
			"rsc/skybox/bottom.jpg",
			"rsc/skybox/front.jpg",
			"rsc/skybox/back.jpg"
		});
		CShader Shader; Shader.Load("shaders/vert_cube.glsl", "shaders/frag_cube.glsl");
		m_Shaders.push_back(Shader);

		CGLMesh* Object = CObjLoader::LoadCube();
		Object->ObjectType = EObjectType::SkyBox;
		Object->SetProgram(Shader.Program);
		Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		Object->SetModel(model);

		//Object->AddUniformParam(new CUniformParam_vec3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor"));
		m_Objects.push_back(Object);
		m_SkyBox = Object;
	}

	if (true)
	{
		CTexture Texture;
		Texture.Load("rsc/box.jpg");
		CShader Shader; Shader.Load("shaders/vert.glsl", "shaders/frag_texture.glsl");
		m_Shaders.push_back(Shader);

		CGLMesh* Object = CObjLoader::Load("rsc/box.obj");
		Object->SetProgram(Shader.Program);
		Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		Object->SetModel(model);

		//Object->AddUniformParam(new CUniformParam_vec3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor"));
		m_Objects.push_back(Object);
		m_Terrain = Object;
	}

	if (true)
	{
		CTexture Texture;
		Texture.Load("rsc/box.jpg");
		CShader Shader; Shader.Load("shaders/vert.glsl", "shaders/frag_texture.glsl");
		m_Shaders.push_back(Shader);

		CGLMesh* Object = CObjLoader::Load("rsc/box.obj");
		Object->SetProgram(Shader.Program);
		Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(10.0f, 10.0f, 0.0f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		Object->SetModel(model);

		//Object->AddUniformParam(new CUniformParam_vec3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor"));
		m_Objects.push_back(Object);
		m_Terrain = Object;
	}

	if (true)
	{
		CTexture Texture;
		Texture.Load("rsc/terrain.jpg");
		CShader Shader; Shader.Load("shaders/vert.glsl", "shaders/frag_texture.glsl");
		m_Shaders.push_back(Shader);

		CGLMesh* Object = CObjLoader::Load("rsc/terrain.obj");
		Object->SetProgram(Shader.Program);
		Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(10.0f, -5.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		model = glm::scale(model, glm::vec3(10.f));
		Object->SetModel(model);

		//Object->AddUniformParam(new CUniformParam_vec3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor"));
		m_Objects.push_back(Object);
		m_Terrain = Object;
	}

	//if (true)
	//{
	//	CTexture Texture;
	//	Texture.Load("rsc/box.jpg");
	//	CShader Shader; Shader.Load("shaders/vert.glsl", "shaders/frag_texture.glsl");
	//	m_Shaders.push_back(Shader);

	//	CGLTerrain* Object = new CGLTerrain();
	//	Object->SetProgram(Shader.Program);
	//	Object->SetTexture(Texture);
	//	CHeightMap HeightMap;
	//	HeightMap.Load("rsc/HeightMap.bmp");
	//	Object->SetHeightMap(HeightMap);
	//	Object->Prepare();

	//	glm::mat4 model;
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//	//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
	//	Object->SetModel(model);

	//	//Object->AddUniformParam(new CUniformParam_vec3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor"));
	//	m_Objects.push_back(Object);
	//	m_Terrain = Object;
	//}

	if (true)
	{
		CTexture Texture;
		Texture.Load("rsc/box.jpg");
		CShader Shader; Shader.Load("shaders/light_vert.glsl", "shaders/light_frag.glsl");
		m_Shaders.push_back(Shader);

		CGLMesh* Object = CObjLoader::Load("rsc/box.obj");
		Object->SetProgram(Shader.Program);
		//Object->SetTexture(Texture);
		Object->Prepare();

		glm::mat4 model;
		model = glm::translate(model, m_LightPos);
		model = glm::scale(model, {0.1f,0.1f, 0.1f});
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		Object->SetModel(model);

		m_Objects.push_back(Object);

		//Object->AddUniformParam(new CUniformParam_vec3({ 1.0f, 0.5f, 0.31f }, "objectColor"));
	}

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DoMovement();

	if (m_OnlyColorPicking)
	{
		m_ColorPicker->Enable();
		m_ColorPicker->Draw(this);
		m_ColorPicker->Disable();
	}
	else
	{
		if (m_ColorPicker->Enabled())
		{
			if (CGLObject* Picked = m_ColorPicker->Pick(this))
			{
				//std::cout << (int)Picked->ObjectType << std::endl;
				auto index = std::distance(m_Objects.begin(), std::find(m_Objects.begin(), m_Objects.end(), Picked));
				cout << "Picked object index " << index << endl;
				PickObject(Picked);
			}
			m_ColorPicker->Disable();
		}
		DrawObjects();
	}

	
}

void CEngine::DrawObjects()
{
	glm::mat4 View = m_Camera.GetView();
	//glm::mat4 Projection = glm::perspective(glm::radians(m_FOV), 800.f / 600.f, 0.1f, 10000.0f);

	const float Near = 0.1f, Far = 10000.f;
	float top, bottom, left, right;
	float Aspect = 800.f / 600.f;
	GLfloat FOV = glm::radians(m_FOV);
	top = Near * tan(FOV / 2);
	bottom = -top;
	right = Aspect * tan(FOV / 2) * Near;
	left = -left;

	glm::mat4 Projection = glm::frustum(left, right, bottom, top, Near, Far);

	std::vector<CUniformParam*> Params;
	Params.push_back(new CUniformParam_mat4(View, "view"));
	Params.push_back(new CUniformParam_mat4(Projection, "projection"));
	//Params.push_back(new CUniformParam_vec3(m_LightPos, "lightPos"));
	//Params.push_back(new CUniformParam_vec3({ 1.0f, 1.0f, 1.0f }, "lightColor"));

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		glm::vec4 PickingColor = m_Objects[i]->GetUniqueColor();
		PickingColor /= 255.f;
		std::vector<CUniformParam*> LocalParams(Params);
		if (m_ColorPicker->Enabled())
		{
			LocalParams.push_back(new CUniformParam_vec4(PickingColor, "PickingColor"));
		}

		switch (m_Objects[i]->ObjectType)
		{
		case EObjectType::SkyBox:
		{
			std::vector<CUniformParam*> Params;
			Params.push_back(new CUniformParam_mat4(glm::mat4(glm::mat3(m_Camera.GetView())), "view"));
			Params.push_back(new CUniformParam_mat4(Projection, "projection"));
			Params.push_back(new CUniformParam_vec4(PickingColor, "PickingColor"));
			m_Objects[i]->Draw(Params);
			break;
		}
		//case 1:
		//{
		//	std::vector<CUniformParam*> Params;
		//	Params.push_back(new CUniformParam_vec3({ 1.0f, 0.5f, 0.31f }, "objectColor"));
		//	m_Objects[i]->Draw(Params);
		//}
		default:
			m_Objects[i]->Draw(LocalParams);
			break;
		}

	}
}

void CEngine::OnKey(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		m_Keys[key] = true;
	else if (action == GLFW_RELEASE)
		m_Keys[key] = false;

	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		if (m_CursorMode == ECursorMode::Normal)
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_CursorMode = ECursorMode::Disabled;
			glfwSetCursorPos(m_Window->GetWindow(), m_LastX, m_LastY);
		}
		else
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_CursorMode = ECursorMode::Normal;
		}
	}

	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
	{
		m_OnlyColorPicking = !m_OnlyColorPicking;
	}
}

void CEngine::OnMouseMove(double xpos, double ypos)
{
	double xoffset = xpos - m_LastX;
	double yoffset = m_LastY - ypos; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
	m_LastX = xpos;
	m_LastY = ypos;

	if (m_CursorMode == ECursorMode::Disabled)
	{
		const double sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Camera.Rotate(static_cast<GLfloat>(xoffset), static_cast<GLfloat>(yoffset));
	}
}

void CEngine::OnScroll(double xoffset, double yoffset)
{
	if (m_FOV >= 1.0f && m_FOV <= 45.0f)
		m_FOV -= static_cast<GLfloat>(yoffset);
	m_FOV = std::max(m_FOV, 1.0f);
	m_FOV = std::min(m_FOV, 45.0f);
}

void CEngine::OnClick(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		m_ColorPicker->Enable();
	}
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

void CEngine::PickObject(CGLObject* Object)
{
	if (m_PickedObject)
	{
		auto Model = m_PickedObject->GetModel();
		m_PickedObject->SetModel(glm::translate(Model, glm::vec3(0.f, -1.f, 0.f)));
	}

	if (Object->ObjectType == EObjectType::SkyBox)
		m_PickedObject = nullptr;
	else if (m_PickedObject != Object)
	{
		m_PickedObject = Object;
		auto Model = m_PickedObject->GetModel();
		m_PickedObject->SetModel(glm::translate(Model, glm::vec3(0.f, 1.f, 0.f)));
	}
	else
		m_PickedObject = nullptr;
}

std::vector<CGLObject*>& CEngine::GetObjects()
{
	return m_Objects;
}

glm::vec<2, double> CEngine::GetCursor() const
{
	return glm::vec<2, double>(m_LastX, m_LastY);
}
