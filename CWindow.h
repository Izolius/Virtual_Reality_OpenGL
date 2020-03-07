#pragma once
struct GLFWwindow;
class CEngine;
class CWindow
{
	GLFWwindow* m_Window;
public:
	CWindow();
	~CWindow();
	void Show(CEngine* Engine);
};

