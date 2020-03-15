#include "stdafx.h"
#include "CEngine.h"
#include "CWindow.h"
#include "ShaderUtils.h"
#include "CObjLoader.h"
#include "CGLObject.h"
#include "CColorPicker.h"
#include <iostream>
using namespace std;

std::ostream& operator<<(std::ostream& stream, EChangedOption option)
{
	switch (option)
	{
	case EChangedOption::FOV:
		stream << "FOV";
		break;
	case EChangedOption::Convergence:
		stream << "Convergence";
		break;
	case EChangedOption::EyeDistance:
		stream << "EyeDistance";
		break;
	default:
		break;
	}
	return stream;
}

CEngine::CEngine(CWindow* Window):
	m_Window(Window), m_LightPos(3.0f, 2.0f, 2.0f)
{
	cout << "c - to switch cursor mode" << endl;
	cout << "m - to switch view mode" << endl;
	cout << "o - to switch changed param" << endl;
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
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
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

	switch (m_ViewMode)
	{
	case EViewMode::Normal:
		if (m_ColorPicker->Enabled())
		{
			if (CGLObject* Picked = m_ColorPicker->Pick(this))
			{
				auto index = std::distance(m_Objects.begin(), std::find(m_Objects.begin(), m_Objects.end(), Picked));
				cout << "Picked object index " << index << endl;
				PickObject(Picked);
			}
			m_ColorPicker->Disable();
		}
		DrawObjects();
		break;
	case EViewMode::ColorPick:
		m_ColorPicker->Enable();
		m_ColorPicker->Draw(this);
		m_ColorPicker->Disable();
		break;
	case EViewMode::Anaglyph:
		m_Camera.SetEyePos(EEyePos::Left);
		glColorMask(true, false, false, false);
		DrawObjects();
		glClear(GL_DEPTH_BUFFER_BIT);
		m_Camera.SetEyePos(EEyePos::Right);
		glColorMask(false, true, true, false);
		DrawObjects();
		glColorMask(true, true, true, true);
		break;
	default:
		break;
	}
}

void CEngine::DrawObjects()
{
	glm::mat4 View = m_Camera.GetView();
	glm::mat4 Projection = GetProjection();

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
			for (auto& param : Params)
				delete param;
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

		if (m_ColorPicker->Enabled())
			delete *LocalParams.rbegin();
	}
	for (auto& param : Params)
		delete param;
}

void CEngine::OnKey(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		m_Keys[key] = true;
	else if (action == GLFW_RELEASE)
		m_Keys[key] = false;

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_C:
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
			break;
		}
		case GLFW_KEY_M:
		{
			m_ViewMode = static_cast<EViewMode>(((int)m_ViewMode + 1) % 3);
			break;
		}
		case GLFW_KEY_O:
		{
			m_ChangedOption = static_cast<EChangedOption>(((int)m_ChangedOption + 1) % 3);
			cout << "Now you are changing " << m_ChangedOption << endl;
			break;
		}
		default:
			break;
		}
	}

}

void CEngine::OnMouseMove(double xpos, double ypos)
{
	double xoffset = xpos - m_LastX;
	double yoffset = m_LastY - ypos;
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && m_ViewMode == EViewMode::Normal)
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
	if (m_Keys[GLFW_KEY_KP_SUBTRACT])
	{
		switch (m_ChangedOption)
		{
		case EChangedOption::FOV:
			OnScroll(0, 0.01);
			cout << m_FOV << endl;
			break;
		case EChangedOption::Convergence:
			m_Convergence -= (m_Far - m_Near) * 0.001f;
			m_Convergence = std::max(m_Near, m_Convergence);
			cout << m_Convergence << endl;
			break;
		case EChangedOption::EyeDistance:
			m_Camera.SetEyeDistance(m_Camera.GetEyeDistance() - 0.0001f);
			cout << m_Camera.GetEyeDistance() << endl;
			break;
		default:
			break;
		}
	}
	if (m_Keys[GLFW_KEY_KP_ADD])
	{
		switch (m_ChangedOption)
		{
		case EChangedOption::FOV:
			OnScroll(0, -0.01);
			cout << m_FOV << endl;
			break;
		case EChangedOption::Convergence:
			m_Convergence += (m_Far - m_Near) * 0.001f;
			m_Convergence = std::min(m_Far, m_Convergence);
			cout << m_Convergence << endl;
			break;
		case EChangedOption::EyeDistance:
			m_Camera.SetEyeDistance(m_Camera.GetEyeDistance() + 0.0001f);
			cout << m_Camera.GetEyeDistance() << endl;
			break;
		default:
			break;
		}
	}
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

const float Aspect = 800.f / 600.f;

glm::mat4 CEngine::GetProjection() const
{
	switch (m_Camera.GetEyePos())
	{
	case EEyePos::Normal:
	{
		float top, bottom, left, right;
		GLfloat FOV = glm::radians(m_FOV);
		top = m_Near * tan(FOV / 2);
		bottom = -top;
		right = Aspect * tan(FOV / 2) * m_Near;
		left = -right;

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glFrustum(left, right, bottom, top, m_Near, m_Far);

		return glm::frustum(left, right, bottom, top, m_Near, m_Far);
	}
	case EEyePos::Left:
		return GetLeftProjection();
	case EEyePos::Right:
		return GetRightProjection();
	default:
		throw exception("bad eye pos");
	}
}

glm::mat4 CEngine::GetLeftProjection() const
{
	float top, bottom, left, right;
	GLfloat FOV = glm::radians(m_FOV);
	top = m_Near * tan(FOV / 2);
	bottom = -top;
	float a = Aspect * tan(FOV / 2) * m_Convergence;
	float b = a - m_Camera.GetEyeDistance() / 2;
	float c = a + m_Camera.GetEyeDistance() / 2;
	left = -b * m_Near / m_Convergence;
	right = c * m_Near / m_Convergence;

	return glm::frustum(left, right, bottom, top, m_Near, m_Far);
}

glm::mat4 CEngine::GetRightProjection() const
{
	float top, bottom, left, right;
	GLfloat FOV = glm::radians(m_FOV);
	top = m_Near * tan(FOV / 2);
	bottom = -top;
	float a = Aspect * tan(FOV / 2) * m_Convergence;
	float b = a - m_Camera.GetEyeDistance() / 2;
	float c = a + m_Camera.GetEyeDistance() / 2;
	left = -c * m_Near / m_Convergence;
	right = b * m_Near / m_Convergence;

	return glm::frustum(left, right, bottom, top, m_Near, m_Far);
}
