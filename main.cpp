#include "stdafx.h"
#include <iostream>
#include <string>
#include "CWindow.h"
#include "CEngine.h"

int main()
{
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	CWindow window;
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	CEngine Engine(&window);
	Engine.Prepare();
	Engine.Start();

	glfwTerminate();
	return 0;
}