#pragma once
class CWindow;
class CEngine
{
	CWindow* m_Window;
	std::vector<CGLObject*> m_Objects;
	std::vector<CShader> m_Shaders;
public:
	CEngine(CWindow* Window);
	void Prepare();
	void Start();
	void OnDrow();
};

