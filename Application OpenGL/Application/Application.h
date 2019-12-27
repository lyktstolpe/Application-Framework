#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include <memory>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

#include "Command/ApplicationCommands.h"
#include "State/StateManager.h"
#include "State/MainState.h"
#include "State/ExtraState.h"
#include "Window.h"

class Application : public std::enable_shared_from_this<Application>
{
private:
	std::unique_ptr<Window> _window;
	std::shared_ptr<StateManager> _statemanager;
	std::shared_ptr<std::shared_ptr<IApplicationState>[size_t(State::count)]> _states;

	bool _printnextfps;

public:
	Application();

	void run();
	void printfps() { _printnextfps = true; }

private:

	void init_logging();
	void init_glew();
	void init_glfw();
	void init_window();
	void init_statemanager();
	void init_states();
	void init_key_bindings();
};

#endif