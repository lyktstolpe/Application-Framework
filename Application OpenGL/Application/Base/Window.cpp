#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN)
		return;
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	userpointer->inputhandler()->key_pressed(key, action);
}

void mouse_key_callback(GLFWwindow* window, int key, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN)
		return;
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	userpointer->inputhandler()->button_pressed(key, action);
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	double normalizedx =  2.0 * (x / userpointer->_width) - 1.0;
	double normalizedy = -2.0 * (y / userpointer->_height) + 1.0;
	userpointer->inputhandler()->cursor_moved(normalizedx, normalizedy);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	userpointer->_width = width;
	userpointer->_height = height;
}

Window::Window(int width, int height, InputHandler* inputhandler)
	: _inputhandler(inputhandler)
	, _width(width)
	, _height(height)
{
	// Setup window
	_glfwwindow = static_cast<std::unique_ptr<GLFWwindow, DestroyglfwWin>>(glfwCreateWindow(_width, _height, "Window", nullptr, nullptr));

	glfwMakeContextCurrent(_glfwwindow.get());
	glfwSetKeyCallback(_glfwwindow.get(), key_callback);
	glfwSetMouseButtonCallback(_glfwwindow.get(), mouse_key_callback);
	glfwSetCursorPosCallback(_glfwwindow.get(), cursor_position_callback);
	glfwSetWindowSizeCallback(_glfwwindow.get(), window_size_callback);
	glfwSetWindowUserPointer(_glfwwindow.get(), this);
}

Window::~Window()
{}

void Window::update()
{
	glfwSwapBuffers(_glfwwindow.get());
}
