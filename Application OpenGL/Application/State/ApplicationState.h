#ifndef STATE_H
#define STATE_H

#pragma once

#include <memory>

#include "../Input/InputHandler.h"
#include "../Input/Context/ContextManager.h"
#include "../Utilities/Timer.h"

#include <GLFW/glfw3.h>

enum class AppState {
	main,
	// Always last
	count
};

class StateManager;

class IApplicationState
{
public:
	IApplicationState() : _userpointer(nullptr) {}

	virtual void init() = 0;
	virtual void cleanup() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	void get_events();
	void update() {
		_contextmanager.attempt_execute_events();
		update_append();
	};
	virtual void display() = 0;

	virtual const char* get_name() = 0;

	template <typename T>
	static void set_userpointer(IApplicationState& state, std::shared_ptr<T> pointer) { state.set_userpointer(&pointer); }
	template <typename T>
	static std::shared_ptr<T> get_userpointer(IApplicationState& state) { return *static_cast<std::shared_ptr<T>*>(state.get_userpointer()); }

private:
	void set_userpointer(void* pointer) { _userpointer = pointer; }
	void* get_userpointer() { return _userpointer; }
	void* _userpointer;

protected:
	std::vector<std::unique_ptr<Context>> _inputcontexts;
	ContextManager _contextmanager;

	virtual void get_events_append() = 0;
	virtual void update_append() = 0;
};

#endif