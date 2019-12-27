#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#pragma once

#include <array>
#include <vector>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

#include "Command/Command.h"
#include "Command/Invoker.h"

class InputHandler
{
private:
	std::unique_ptr<Invoker> _invoker;
	std::array<std::shared_ptr<ICommand>, GLFW_KEY_LAST + 1> _commandkeymap;
	std::array<KeyState, GLFW_KEY_LAST + 1> _statemap;
	std::array<std::shared_ptr<ICommand>, GLFW_MOUSE_BUTTON_LAST + 1> _commandmousekeymap;
	std::array<KeyState, GLFW_MOUSE_BUTTON_LAST + 1> _mousestatemap;
	std::vector<int> _constmappedkeys;

public:
	InputHandler();

	void map_key(int key, std::shared_ptr<ICommand> command);
	void map_key_const(int key, std::shared_ptr<ICommand> command);
	void map_mouse_key(int key, std::shared_ptr<ICommand> command);
	void key_event(int key, int action);
	void mouse_key_event(int key, int action);
	void execute_command_queue();
};

#endif