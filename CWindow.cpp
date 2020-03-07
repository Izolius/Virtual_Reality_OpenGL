#include "stdafx.h"
#include "CWindow.h"
#include <iostream>
#include "CEngine.h"
using namespace std;

namespace {
	GLFWwindow* window;
	CEngine* engine;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else
	{
		engine->OnKey(key, scancode, action, mode);
	}
}

CWindow::CWindow()
{
	m_Window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	window = m_Window;
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		abort();
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetKeyCallback(m_Window, key_callback);
}

CWindow::~CWindow()
{
	glfwDestroyWindow(m_Window);
	window = nullptr;
}

void CWindow::Show(CEngine* Engine)
{
	engine = Engine;
	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		// ��������� ������� � �������� ������� ��������� ������.
		glfwPollEvents();

		Engine->OnDrow();
		
		// ������ ������ �������
		glfwSwapBuffers(window);
	}
}
