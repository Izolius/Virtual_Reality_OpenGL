#pragma once
#include "CCamera.h"
#include "CTexture.h"

class CWindow;
class CGLObject;
class CColorPicker;

enum class ECursorMode
{
	Normal,
	Disabled
};

class CEngine
{
	CWindow* m_Window;
	std::vector<CGLObject*> m_Objects;
	CGLObject* m_Terrain;
	CGLObject* m_SkyBox;
	std::vector<CShader> m_Shaders;
	std::vector<CTexture> m_Textures;
	CCamera m_Camera;
	std::array<bool, 1024> m_Keys;
	double m_LastFrame = 0.0f, m_DeltaTime;
	double m_LastX = 400, m_LastY = 300;
	GLfloat m_FOV = 45.0f;
	ECursorMode m_CursorMode = ECursorMode::Disabled;

	glm::vec3 m_LightPos;
	std::unique_ptr<CColorPicker> m_ColorPicker;
	bool m_OnlyColorPicking = false;
	CGLObject* m_PickedObject;
	
public:
	CEngine(CWindow* Window);
	~CEngine();
	void Prepare();
	void Start();
	void OnDrow();
	void DrawObjects();
	void OnKey(int key, int scancode, int action, int mode);
	void OnMouseMove(double xpos, double ypos);
	void OnScroll(double xoffset, double yoffset);
	void OnClick(int button, int action, int mods);
	void DoMovement();
	void PickObject(CGLObject* Object);

	std::vector<CGLObject*>& GetObjects();
	glm::vec<2, double> GetCursor() const;
};

