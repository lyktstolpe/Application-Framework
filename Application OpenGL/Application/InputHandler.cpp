#include "InputHandler.h"

InputHandler::InputHandler()
	: _commandkeymap()
	, _statemap()
	, _commandmousekeymap()
	, _mousestatemap()
{
	_invoker = std::make_unique<Invoker>();
}

void InputHandler::map_key(int key, std::shared_ptr<ICommand> command)
{
	for (auto& k : _constmappedkeys)
		if (key == k)
			return;
	_commandkeymap[key] = command;
}

void InputHandler::map_key_const(int key, std::shared_ptr<ICommand> command)
{
	_commandkeymap[key] = command;
	_constmappedkeys.push_back(key);
}

void InputHandler::map_mouse_key(int key, std::shared_ptr<ICommand> command)
{
	_commandmousekeymap[key] = command;
}

void InputHandler::key_event(int key, int action)
{
	if (key > GLFW_KEY_LAST)
	{
		LOG_F(WARNING, "Invalid key pressed. Code: %i", key);
		return;
	}

	KeyState previousstate = _statemap[key];

	if (_commandkeymap[key])
	{
		if (action == GLFW_PRESS &&
			previousstate == KeyState::release &&
			_commandkeymap[key]->activation_type() == ActivationType::press)
		{
			_invoker->submit_command(_commandkeymap[key]);
		}

		if ((action == GLFW_REPEAT || action == GLFW_PRESS) &&
			_commandkeymap[key]->activation_type() == ActivationType::hold)
		{
			_invoker->submit_command(_commandkeymap[key]);
		}
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_statemap[key] = KeyState::press;

	if (action == GLFW_RELEASE)
		_statemap[key] = KeyState::release;
}

void InputHandler::mouse_key_event(int key, int action)
{
	if (key > GLFW_MOUSE_BUTTON_LAST)
	{
		LOG_F(WARNING, "Invalid mouse key pressed. Code: %i", key);
		return;
	}

	std::shared_ptr<ICommand> command = _commandmousekeymap[key];
	KeyState previousstate = _mousestatemap[key];

	if (command)
	{
		if (action == GLFW_PRESS &&
			previousstate == KeyState::release &&
			command->activation_type() == ActivationType::press)
		{
			_invoker->submit_command(command);
		}

		if ((action == GLFW_REPEAT || action == GLFW_PRESS) &&
			command->activation_type() == ActivationType::hold)
		{
			_invoker->submit_command(command);
		}
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_mousestatemap[key] = KeyState::press;

	if (action == GLFW_RELEASE)
		_mousestatemap[key] = KeyState::release;
}

void InputHandler::execute_command_queue()
{
	_invoker->flush_queue();
}
