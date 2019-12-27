#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	userpointer->inputhandler()->key_event(key, action);
}

void mouse_key_callback(GLFWwindow* window, int key, int action, int mods)
{
	Window* userpointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
	userpointer->inputhandler()->mouse_key_event(key, action);
}

Window::Window()
{
	// Setup window
	_glfwwindow = static_cast<std::unique_ptr<GLFWwindow, DestroyglfwWin>>(glfwCreateWindow(720, 480, "Window", nullptr, nullptr));

	glfwMakeContextCurrent(_glfwwindow.get());
	glfwSetKeyCallback(_glfwwindow.get(), key_callback);
	glfwSetMouseButtonCallback(_glfwwindow.get(), mouse_key_callback);
	glfwSetWindowUserPointer(_glfwwindow.get(), this);

	// Pointers
	_inputhandler = std::make_shared<InputHandler>();
}

Window::~Window()
{}

void Window::update()
{
	glfwPollEvents();
	_inputhandler->execute_command_queue();
	glfwSwapBuffers(_glfwwindow.get());
}
