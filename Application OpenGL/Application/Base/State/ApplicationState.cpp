#include "ApplicationState.h"
#include "../Application_Base.h"

void ApplicationState::cleanup_core()
{
	clear_context();
	_inputcontexts.clear();
	cleanup();
}

void ApplicationState::get_events_core()
{
	auto parentapp_shared = _parentapplication.lock();
	std::unique_ptr<std::vector<KeyEvent>> key_events = parentapp_shared->get_inputhandler()->get_key_events();
	if (!_contextmanager.handle_key_events(key_events))
	{
		int released = 0;
		int pressed = 0;
		for (auto e : *key_events)
		{
			if (e.type == KeyEventType::key_pressed)
				pressed++;
			if (e.type == KeyEventType::key_released)
				released++;
		}
		if (released)
			LOG_F(INFO, "Key released events not handled:\t %i", released);
		if (pressed)
			LOG_F(INFO, "Key pressed events not handled:\t %i", pressed);
	}

	std::unique_ptr<std::vector<MouseEvent>> mouse_events = parentapp_shared->get_inputhandler()->get_mouse_events();
	if (!_contextmanager.handle_mouse_events(mouse_events))
	{
		int buttonevents = 0;
		for (auto& e : *mouse_events)
			if (e.type != MouseEventType::moved)
				buttonevents++;
		if (buttonevents)
			LOG_F(INFO, "Mouse events not handled: %i", buttonevents);
	}
	get_events();
}

void ApplicationState::update_core()
{
	_contextmanager.attempt_execute_events();
	update();
}

void ApplicationState::display_core()
{
	display();
}

void ApplicationState::change_to_context(int i)
{
	if (i < _inputcontexts.size())
		_contextmanager.change_context(_inputcontexts[i].get());
}

void ApplicationState::push_context(int i)
{
	if (i < _inputcontexts.size())
		_contextmanager.push_context(_inputcontexts[i].get());
}

void ApplicationState::pop_context()
{
	_contextmanager.pop_context();
}

void ApplicationState::clear_context()
{
	_contextmanager.clear();
}

std::unique_ptr<Command::ChangeContext> ApplicationState::get_command_change_to_context(int i)
{
	std::unique_ptr<Command::ChangeContext> cmd = std::make_unique<Command::ChangeContext>(this, i);
	return std::move(cmd);
}
