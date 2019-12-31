#include "InputHandler.h"

InputHandler::InputHandler()
	: _key_statemap()
	, _button_statemap()
	, _cursorx(0)
	, _cursory(0)
{
	std::unique_ptr<std::vector<KeyEvent>> temp_key_events =
		std::make_unique< std::vector<KeyEvent>>();
	_key_events.swap(temp_key_events);

	std::unique_ptr<std::vector<MouseEvent>> temp_mouse_events =
		std::make_unique< std::vector<MouseEvent>>();
	_mouse_events.swap(temp_mouse_events);
}

void InputHandler::key_pressed(int key, int action)
{
	if (key > GLFW_KEY_LAST)
	{
		LOG_F(WARNING, "Invalid key pressed. Code: %i", key);
		return;
	}
	
	KeyState previousstate = _key_statemap[key];
	KeyState currentstate = action == GLFW_RELEASE ? KeyState::release : KeyState::press;

	if (currentstate == KeyState::press && previousstate == KeyState::release)
		_key_events->push_back(KeyEvent(KeyEventType::key_pressed, key));

	if (currentstate == KeyState::release)
		_key_events->push_back(KeyEvent(KeyEventType::key_released, key));

	_key_statemap[key] = currentstate;
}

void InputHandler::button_pressed(int key, int action)
{
	if (key > GLFW_KEY_LAST)
	{
		LOG_F(WARNING, "Invalid button pressed. Code: %i", key);
		return;
	}

	KeyState previousstate = _button_statemap[key];
	KeyState currentstate = action == GLFW_RELEASE ? KeyState::release : KeyState::press;

	if (currentstate == KeyState::press && previousstate == KeyState::release)
		_mouse_events->push_back(MouseEvent(_cursorx, _cursory, MouseEventType::button_pressed, key));

	if (currentstate == KeyState::release)
		_mouse_events->push_back(MouseEvent(_cursorx, _cursory, MouseEventType::button_released, key));

	_button_statemap[key] = currentstate;
}

void InputHandler::cursor_moved(double x, double y)
{
	_cursorx = x;
	_cursory = y;

	_mouse_events->push_back(MouseEvent(x, y, MouseEventType::moved));
}

std::unique_ptr<std::vector<KeyEvent>> InputHandler::get_key_events()
{
	std::unique_ptr<std::vector<KeyEvent>> temp_key_events = 
		std::make_unique<std::vector<KeyEvent>>();
	_key_events.swap(temp_key_events);
	return temp_key_events;
}

std::unique_ptr<std::vector<MouseEvent>> InputHandler::get_mouse_events()
{
	std::unique_ptr<std::vector<MouseEvent>> temp_mouse_events =
		std::make_unique<std::vector<MouseEvent>>();
	_mouse_events.swap(temp_mouse_events);
	return temp_mouse_events;
}
