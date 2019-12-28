#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <GLFW/glfw3.h>

#include "Input/InputHandler.h"

struct DestroyglfwWin {
	void operator()(GLFWwindow* ptr) {
		glfwDestroyWindow(ptr);
	}
};

class Window
{
private:
	std::unique_ptr<GLFWwindow, DestroyglfwWin> _glfwwindow;
	InputHandler* _inputhandler;

public:
	Window(InputHandler* inputhandler);
	~Window();

	void update();

	bool is_closed() { return glfwWindowShouldClose(_glfwwindow.get()); }
	InputHandler* inputhandler() { return _inputhandler; }
	GLFWwindow* glfwwindow() { return _glfwwindow.get(); }
};

#endif