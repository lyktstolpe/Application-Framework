#include "DefaultCommands.h"
#include "../Application_Base.h"

Print::Print(std::string string)
	: _string(string)
{}

void Print::execute()
{
	LOG_F(INFO, "%s", _string.c_str());
}

ChangeState::ChangeState(Application* app, int index)
	: _app(app)
	, _index(index)
{}

void ChangeState::execute()
{
	LOG_F(INFO, "Changing state...");
	_app->set_flag_change_state(_index);
}

DisableCursor::DisableCursor(GLFWwindow* window)
	: _window(window)
{}

void DisableCursor::execute()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

EnableCursor::EnableCursor(GLFWwindow* window)
	: _window(window)
{}

void EnableCursor::execute()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

ToggleCursor::ToggleCursor(GLFWwindow* window)
	: _window(window)
{}

void ToggleCursor::execute()
{
	int mode = glfwGetInputMode(_window, GLFW_CURSOR);
	if (mode == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (mode == GLFW_CURSOR_DISABLED)
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}