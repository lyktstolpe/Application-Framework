#include "InputHandler.h"

InputHandler::InputHandler()
	: _key_statemap()
	, _mouse_button_statemap()
{
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> temp_key_events =
		std::make_unique< std::vector<std::unique_ptr<KeyEvent>>>();
	_key_events.swap(temp_key_events);
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> temp_mouse_button_events =
		std::make_unique< std::vector<std::unique_ptr<KeyEvent>>>();
	_mouse_button_events.swap(temp_mouse_button_events);
}

void InputHandler::key_event(int key, int action)
{
	if (key > GLFW_KEY_LAST)
	{
		LOG_F(WARNING, "Invalid key pressed. Code: %i", key);
		return;
	}

	// If no more than one event per key is to be created before events are handled
	//for (auto& e : *_keyevents)
	//	if (e->get_key() == key)
	//		return;

	KeyState previousstate = _key_statemap[key];
	KeyState currentstate = action == GLFW_RELEASE ? KeyState::release : KeyState::press;

	if (currentstate == KeyState::press && previousstate == KeyState::release)
		_key_events->push_back(std::move(std::make_unique<KeyEvent>(key, KeyEventType::key_pressed)));

	if (currentstate == KeyState::release)
		_key_events->push_back(std::move(std::make_unique<KeyEvent>(key, KeyEventType::key_released)));

	_key_statemap[key] = currentstate;
}

void InputHandler::mouse_key_event(int key, int action)
{
	if (key > GLFW_MOUSE_BUTTON_LAST)
	{
		LOG_F(WARNING, "Invalid mouse key pressed. Code: %i", key);
		return;
	}

	// If no more than one event per key is to be created before events are handled
	//for (auto& e : *_mouse_buttonevents)
	//	if (e->get_key() == key)
	//		return;

	KeyState previousstate = _mouse_button_statemap[key];
	KeyState currentstate = action == GLFW_RELEASE ? KeyState::release : KeyState::press;

	if (currentstate == KeyState::press && previousstate == KeyState::release)
			_mouse_button_events->push_back(std::move(std::make_unique<KeyEvent>(key, KeyEventType::key_pressed)));

	if (currentstate == KeyState::release)
		_mouse_button_events->push_back(std::move(std::make_unique<KeyEvent>(key, KeyEventType::key_released)));

	_mouse_button_statemap[key] = currentstate;
}

std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> InputHandler::get_key_events()
{
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> temp_key_events = 
		std::make_unique< std::vector<std::unique_ptr<KeyEvent>>>();
	_key_events.swap(temp_key_events);
	return temp_key_events;
}

std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> InputHandler::get_mouse_button_events()
{
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> temp_mouse_button_events =
		std::make_unique< std::vector<std::unique_ptr<KeyEvent>>>();
	_mouse_button_events.swap(temp_mouse_button_events);
	return temp_mouse_button_events;
}
