#pragma once

#include "Command_Base.h"

namespace Command
{
	class Print : public Command
	{
	public:
		Print(std::string string);

		void execute();

	private:
		std::string _string;
	};

	class ChangeState : public Command
	{
	public:
		ChangeState(::Application* app, int index);

		void execute();

	private:
		::Application* _app;
		int _index;
	};

	class ChangeContext : public Command
	{
	public:
		ChangeContext(::ApplicationState* state, int index);

		void execute();

	private:
		::ApplicationState* _state;
		int _index;
	};

	class DisableCursor : public Command
	{
	public:
		DisableCursor(GLFWwindow* window);

		void execute();

	private:
		GLFWwindow* _window;
	};

	class EnableCursor : public Command
	{
	public:
		EnableCursor(GLFWwindow* window);

		void execute();

	private:
		GLFWwindow* _window;
	};

	class ToggleCursor : public Command
	{
	public:
		ToggleCursor(GLFWwindow* window);

		void execute();

	private:
		GLFWwindow* _window;
	};
}