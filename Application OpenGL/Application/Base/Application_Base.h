#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include <memory>

#include <loguru.hpp>
#include <GLFW/glfw3.h>

#include "State/StateManager.h"
#include "Window.h"

class Application : public std::enable_shared_from_this<Application>
{
public:
	Application();
	virtual ~Application() {}

	void init();
	void run();
	void update();
	InputHandler* get_inputhandler() { return _inputhandler.get(); }
	StateManager* get_statemanager() { return _statemanager.get(); }
	void printfps() { _printnextfps = true; }

	template<class statetype, typename ...Args>
	void create_state(Args ...args)
	{
		_states.push_back(std::make_shared<statetype>(std::forward<Args>(args)...));
		auto& s = _states.back();
		s->_parentapplication = shared_from_this();
		s->_glfwwindow = _window->glfwwindow();
	}

	void change_to_state(int i)
	{
		if (i < _states.size())
			_statemanager->change_state(_states[i].get());
	}

	std::unique_ptr<Command::ChangeState> get_command_change_to_state(int i)
	{
		std::unique_ptr<Command::ChangeState> cmd = std::make_unique<Command::ChangeState>(this, i);
		return std::move(cmd);
	}

	void set_flag_change_state(int i)
	{
		_flag_change_state = i;
	}

private:
	void init_logging();
	void init_glew();
	void init_glfw();
	void init_inputhandler();
	void init_window();
	void init_statemanager();
	virtual void init_states() = 0;

private:
	std::unique_ptr<Window> _window;
	std::unique_ptr<InputHandler> _inputhandler;
	std::unique_ptr<StateManager> _statemanager;
	std::vector<std::shared_ptr<IApplicationState>> _states;

	bool _printnextfps;
	int _flag_change_state;
};

#endif