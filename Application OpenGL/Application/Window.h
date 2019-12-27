#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <GLFW/glfw3.h>

#include "InputHandler.h"

struct DestroyglfwWin {
	void operator()(GLFWwindow* ptr) {
		glfwDestroyWindow(ptr);
	}
};

class Window
{
private:
	std::unique_ptr<GLFWwindow, DestroyglfwWin> _glfwwindow;
	std::shared_ptr<InputHandler> _inputhandler;

public:
	Window();
	~Window();

	void update();

	bool is_closed() { return glfwWindowShouldClose(_glfwwindow.get()); }
	std::shared_ptr<InputHandler> inputhandler() { return _inputhandler; }
	GLFWwindow* glfwwindow() { return _glfwwindow.get(); }
};

#endif