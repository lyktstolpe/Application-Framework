#ifndef STATE_H
#define STATE_H

#pragma once

#include <memory>

#include "../Input/InputHandler.h"
#include "../Input/Context/ContextManager.h"
#include "../Utilities/Timer.h"

#include <GLFW/glfw3.h>

class Application;

class IApplicationState
{
friend class Application;

public:
	IApplicationState() 
		: _glfwwindow(nullptr)
		, _parentapplication(nullptr)
	{}

	virtual void init() = 0;
	void cleanup_core();
	virtual void pause() = 0;
	virtual void resume() = 0;
	void get_events_core();
	void update_core();
	void display_core();

	virtual const char* get_name() = 0;

	// Function wrappers
	template<class contexttype, typename ...Args>
	void create_context(Args... args)
	{
		_inputcontexts.push_back(std::move(std::make_unique<contexttype>(std::forward<Args>(args)...)));
		_inputcontexts.back()->_glfwwindow = _glfwwindow;
		_inputcontexts.back()->_parentapplication = _parentapplication;
	}
	void change_context(int i);
	void push_context(int i);
	void pop_context();
	void clear_context();

protected:
	std::vector<std::unique_ptr<Context>> _inputcontexts;
	ContextManager _contextmanager;
	std::shared_ptr<GLFWwindow> _glfwwindow;
	std::shared_ptr<Application> _parentapplication;

	virtual void cleanup() = 0;
	virtual void get_events() = 0;
	virtual void update() = 0;
	virtual void display() = 0;
};

#endif