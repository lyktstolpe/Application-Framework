#pragma once

#include <vector>

#include "Context.h"

class ContextManager
{
public:
	ContextManager();

	void change_context(Context* context);
	void push_context(Context* context);
	void pop_context();
	void clear();
	bool handle_key_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events);
	bool handle_mouse_button_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events);
	void attempt_execute_events();
	Context* get_current() { return _stack.back(); }

private:
	std::vector<Context*> _stack;
};