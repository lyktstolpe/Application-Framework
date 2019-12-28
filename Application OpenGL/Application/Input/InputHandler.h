#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#pragma once

#include <array>
#include <vector>

#include <loguru.hpp>

#include "../Command/Command.h"
#include "../Event/InputEvent.h"

#include <GLFW/glfw3.h>

enum class KeyState {
	release,
	press,
};

class InputHandler
{
private:
	std::array<KeyState, GLFW_KEY_LAST + 1> _key_statemap;
	std::array<KeyState, GLFW_MOUSE_BUTTON_LAST + 1> _mouse_button_statemap;
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> _key_events;
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> _mouse_button_events;

public:
	InputHandler();

	void key_event(int key, int action);
	void mouse_key_event(int key, int action);
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> get_key_events();
	std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>> get_mouse_button_events();
};

#endif