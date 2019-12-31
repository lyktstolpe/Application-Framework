#pragma once

#include "ICommand.h"

class Print : public ICommand
{
public:
	Print(std::string string);

	void execute();

private:
	std::string _string;
};

class ChangeState : public ICommand
{
public:
	ChangeState(Application* app, int index);

	void execute();

private:
	Application* _app;
	int _index;
};

class DisableCursor : public ICommand
{
public:
	DisableCursor(GLFWwindow* window);

	void execute();

private:
	GLFWwindow* _window;
};

class EnableCursor : public ICommand
{
public:
	EnableCursor(GLFWwindow* window);

	void execute();

private:
	GLFWwindow* _window;
};

class ToggleCursor : public ICommand
{
public:
	ToggleCursor(GLFWwindow* window);

	void execute();

private:
	GLFWwindow* _window;
};