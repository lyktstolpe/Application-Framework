#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#pragma once

#include <array>
#include <vector>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

#include "../Command/Command.h"
#include "../Event/InputEvent.h"


enum class KeyState {
	release,
	press,
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler() {}

	void key_pressed(int key, int action);
	void button_pressed(int key, int action);
	void cursor_moved(double x, double y);
	std::unique_ptr<std::vector<KeyEvent>> get_key_events();
	std::unique_ptr<std::vector<MouseEvent>> get_mouse_events();

private:
	std::array<KeyState, GLFW_KEY_LAST + 1> _key_statemap;
	std::array<KeyState, GLFW_MOUSE_BUTTON_LAST + 1> _button_statemap;
	std::unique_ptr<std::vector<KeyEvent>> _key_events;
	std::unique_ptr<std::vector<MouseEvent>> _mouse_events;
	double _cursorx, _cursory;
};

#endif