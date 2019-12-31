#include "ApplicationState.h"
#include "../Application_Base.h"

void IApplicationState::cleanup_core()
{
	clear_context();
	cleanup();
}

void IApplicationState::get_events_core()
{
	std::unique_ptr<std::vector<KeyEvent>> key_events = _parentapplication->get_inputhandler()->get_key_events();
	if (!_contextmanager.handle_key_events(key_events))
		LOG_F(INFO, "Key events not handled: %i", int(key_events->size()));

	std::unique_ptr<std::vector<MouseEvent>> mouse_events = _parentapplication->get_inputhandler()->get_mouse_events();
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

void IApplicationState::update_core()
{
	_contextmanager.attempt_execute_events();
	update();
}

void IApplicationState::display_core()
{
	display();
}

void IApplicationState::change_context(int i)
{
	_contextmanager.change_context(_inputcontexts[i].get());
}

void IApplicationState::push_context(int i)
{
	_contextmanager.push_context(_inputcontexts[i].get());
}

void IApplicationState::pop_context()
{
	_contextmanager.pop_context();
}

void IApplicationState::clear_context()
{
	_contextmanager.clear();
}
