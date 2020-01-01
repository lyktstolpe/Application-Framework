#pragma once

#include "ICommand.h"

namespace Command
{
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
		ChangeState(::Application* app, int index);

		void execute();

	private:
		::Application* _app;
		int _index;
	};

	class ChangeContext : public ICommand
	{
	public:
		ChangeContext(::IApplicationState* state, int index);

		void execute();

	private:
		::IApplicationState* _state;
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
}