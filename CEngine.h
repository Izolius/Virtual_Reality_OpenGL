#pragma once
#include "CCamera.h"
#include "CTexture.h"
class CWindow;
class CGLObject;
class CEngine
{
	CWindow* m_Window;
	std::vector<CGLObject*> m_Objects;
	CGLObject* m_Terrain;
	std::vector<CShader> m_Shaders;
	std::vector<CTexture> m_Textures;
	CCamera m_Camera;
	std::array<bool, 1024> m_Keys;
	double m_LastFrame = 0.0f, m_DeltaTime;
	double m_LastX = 400, m_LastY = 300;
	GLfloat m_FOV = 45.0f;

	glm::vec3 m_LightPos = { 1.2f, 1.0f, 2.0f };
	
public:
	CEngine(CWindow* Window);
	~CEngine();
	void Prepare();
	void Start();
	void OnDrow();
	void OnKey(int key, int scancode, int action, int mode);
	void OnMouseMove(double xpos, double ypos);
	void OnScroll(double xoffset, double yoffset);
	void DoMovement();
};

