#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include <memory>

#include <loguru.hpp>

#include "State/StateManager.h"
#include "MainState/MainState.h"
#include "Window.h"

#include <GLFW/glfw3.h>

class Application : public std::enable_shared_from_this<Application>
{
public:
	Application();

	void run();
	InputHandler* get_inputhandler() { return _inputhandler.get(); }
	StateManager* get_statemanager() { return _statemanager.get(); }
	void printfps() { _printnextfps = true; }

private:
	void init_logging();
	void init_glew();
	void init_glfw();
	void init_inputhandler();
	void init_window();
	void init_statemanager();

public:

private:
	std::unique_ptr<Window> _window;
	std::unique_ptr<InputHandler> _inputhandler;
	std::unique_ptr<StateManager> _statemanager;
	std::array<std::unique_ptr<IApplicationState, std::default_delete<IApplicationState>>, size_t(AppState::count)> _states;

	bool _printnextfps;

	void init_states();
};

#endif