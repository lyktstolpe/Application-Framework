#ifndef STATE_H
#define STATE_H

#pragma once

#include <memory>

#include <GLFW/glfw3.h>

#include "../Command/Command.h"
#include "../InputHandler.h"
#include "../Utilities/Timer.h"

enum class State {
	main,
	extra,
	// Always last
	count
};

struct StateInfo {
	std::shared_ptr<std::shared_ptr<ICommand>[size_t(State::count)]> changestatecommands;
	std::shared_ptr<InputHandler> inputhandler;
};

class IApplicationState
{
public:
	IApplicationState()
		: _previoustime(0)
	{}
	IApplicationState(StateInfo* createinfo)
		: _changestatecommands(createinfo->changestatecommands)
		, _inputhandler(createinfo->inputhandler)
		, _previoustime(0)
	{
		_timer = std::make_unique<Timer>();
		_timer->reset();
	}

	virtual void init() = 0;
	virtual void cleanup() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void get_events() = 0;
	virtual void update() = 0;
	virtual void display() = 0;

	void printinfo() {
		double currenttime = _timer->elapsed();
		LOG_F(INFO, "Frametime: %f\tState::%s", currenttime - _previoustime, get_name());
		_previoustime = currenttime;
	};

	virtual const char* get_name() = 0;

protected:
	std::shared_ptr<std::shared_ptr<ICommand>[size_t(State::count)]> _changestatecommands;
	std::shared_ptr<InputHandler> _inputhandler;
	std::unique_ptr<Timer> _timer;
	double _previoustime;
};

#endif