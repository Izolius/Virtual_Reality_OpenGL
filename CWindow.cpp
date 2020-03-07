#include "stdafx.h"
#include "CWindow.h"
#include <iostream>
#include "CEngine.h"
using namespace std;

namespace {
	GLFWwindow* window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
	// Игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		// Проверяем события и вызываем функции обратного вызова.
		glfwPollEvents();

		// Команды отрисовки здесь
		//...

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Engine->OnDrow();
		
		// Меняем буферы местами
		glfwSwapBuffers(window);
	}
}
