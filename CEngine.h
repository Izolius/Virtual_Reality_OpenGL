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

enum class EViewMode
{
	Normal,
	ColorPick,
	Anaglyph
};

enum class EChangedOption
{
	FOV,
	Convergence,
	EyeDistance
};

std::ostream& operator<<(std::ostream& stream, EChangedOption option);


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
	GLfloat m_Convergence = 1.0f;
	float m_Near = 0.1f, m_Far = 10.f;
	ECursorMode m_CursorMode = ECursorMode::Disabled;
	EChangedOption m_ChangedOption = EChangedOption::FOV;

	glm::vec3 m_LightPos;
	std::unique_ptr<CColorPicker> m_ColorPicker;
	EViewMode m_ViewMode = EViewMode::Normal;
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
	glm::mat4 GetProjection() const;
	glm::mat4 GetLeftProjection() const;
	glm::mat4 GetRightProjection() const;
};

