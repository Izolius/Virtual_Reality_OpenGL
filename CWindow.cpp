#include "stdafx.h"
#include "CWindow.h"
#include <iostream>
#include "CEngine.h"
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	CEngine* engine = reinterpret_cast<CEngine*>(glfwGetWindowUserPointer(window));
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else
	{
		engine->OnKey(key, scancode, action, mode);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	CEngine* engine = reinterpret_cast<CEngine*>(glfwGetWindowUserPointer(window));
	engine->OnMouseMove(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	CEngine* engine = reinterpret_cast<CEngine*>(glfwGetWindowUserPointer(window));
	engine->OnScroll(xoffset, yoffset);
}

void click_callback(GLFWwindow* window, int button, int action, int mods)
{
	CEngine* engine = reinterpret_cast<CEngine*>(glfwGetWindowUserPointer(window));
	engine->OnClick(button, action, mods);
}

CWindow::CWindow()
{
	m_Window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		abort();
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetMouseButtonCallback(m_Window, click_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

CWindow::~CWindow()
{
	glfwDestroyWindow(m_Window);
}

void CWindow::Show(CEngine* Engine)
{
	glfwSetWindowUserPointer(m_Window, Engine);
	// Игровой цикл
	while (!glfwWindowShouldClose(m_Window))
	{
		// Проверяем события и вызываем функции обратного вызова.
		glfwPollEvents();

		Engine->OnDrow();
		
		// Меняем буферы местами
		glfwSwapBuffers(m_Window);
	}
}

GLFWwindow* CWindow::GetWindow()
{
	return m_Window;
}
