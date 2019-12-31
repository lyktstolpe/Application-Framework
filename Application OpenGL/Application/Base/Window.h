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

public:
	Window(int width, int height, InputHandler* inputhandler);
	~Window();

	void update();

	bool is_closed() { return glfwWindowShouldClose(_glfwwindow.get()); }
	InputHandler* inputhandler() { return _inputhandler; }
	std::shared_ptr<GLFWwindow> glfwwindow() { return _glfwwindow; }

public:
	int _width, _height;

private:
	std::shared_ptr<GLFWwindow> _glfwwindow;
	InputHandler* _inputhandler;
};

#endif