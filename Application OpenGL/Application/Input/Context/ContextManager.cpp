#include "ContextManager.h"

ContextManager::ContextManager()
	: _stack()
{}

void ContextManager::change_context(Context* context)
{
	if (!context)
	{
		LOG_F(WARNING, "Tried to change to non-existent context.");
		return;
	}

	if (!_stack.empty())
	{
		_stack.pop_back();
	}

	_stack.push_back(context);
}

void ContextManager::push_context(Context* context)
{
	if (!context)
	{
		LOG_F(WARNING, "Tried to push non-existent context.");
		return;
	}

	_stack.push_back(context);
}

void ContextManager::pop_context()
{
	if (!_stack.empty())
	{
		_stack.pop_back();
	}
}

void ContextManager::clear()
{
	while (!_stack.empty())
	{
		_stack.pop_back();
	}
}

bool ContextManager::handle_key_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events)
{
	for (int i = int(_stack.size()) - 1; i >= 0; --i)
	{
		_stack[i]->handle_key_events(events);
	}

	return events->empty();
}

bool ContextManager::handle_mouse_button_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events)
{
	for (int i = int(_stack.size()) - 1; i >= 0; --i)
	{
		_stack[i]->handle_mouse_button_events(events);
	}

	return events->empty();
}

void ContextManager::attempt_execute_events()
{
	for (int i = int(_stack.size()) - 1; i >= 0; --i)
	{
		_stack[i]->attempt_execute_events();
	}
}
