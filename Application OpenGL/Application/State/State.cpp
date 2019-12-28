#include "ApplicationState.h"
#include "../Application.h"

void IApplicationState::get_events()
{
	std::shared_ptr<Application> app = IApplicationState::get_userpointer<Application>(*this);
	
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> key_events = app->get_inputhandler()->get_key_events();
	if (!_contextmanager.handle_key_events(key_events))
	{
		LOG_F(INFO, "State::%s: Key events not handled: %i", get_name(), int(key_events->size()));

		for (auto& e : *key_events)
		{
			if (e->get_type() == KeyEventType::key_pressed)
				LOG_F(INFO, "Key: %i\tEvent: pressed", e->get_key());
			else if (e->get_type() == KeyEventType::key_released)
				LOG_F(INFO, "Key: %i\tEvent: released", e->get_key());
		}
	}

	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> mouse_button_events = app->get_inputhandler()->get_mouse_button_events();
	if (!_contextmanager.handle_mouse_button_events(mouse_button_events))
	{
		LOG_F(INFO, "State::%s: Mouse button events not handled: %i", get_name(), int(mouse_button_events->size()));

		for (auto& e : *mouse_button_events)
		{
			if (e->get_type() == KeyEventType::key_pressed)
				LOG_F(INFO, "Mouse Button: %i\tEvent: pressed", e->get_key());
			else if (e->get_type() == KeyEventType::key_released)
				LOG_F(INFO, "Mouse Button: %i\tEvent: released", e->get_key());
		}
	}

	get_events_append();
}