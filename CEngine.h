#pragma once
class CWindow;
class CEngine
{
	CWindow* m_Window;
	std::vector<CGLObject*> m_Objects;
	std::vector<CShader> m_Shaders;
	std::vector<CTexture> m_Textures;
	glm::mat4 m_View, m_Projection;
public:
	CEngine(CWindow* Window);
	~CEngine();
	void Prepare();
	void Start();
	void OnDrow();
	void OnKey(int key, int scancode, int action, int mode);
};

