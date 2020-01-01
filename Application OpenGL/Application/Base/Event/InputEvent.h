#pragma once

enum class KeyEventType {
	key_pressed,
	key_released,
	// Always last
	count
};

enum class MouseEventType {
	button_pressed,
	button_released,
	moved,
	count
};

struct KeyEvent
{
	KeyEvent(KeyEventType t, int k) : key(k), type(t) {}
	~KeyEvent() {}
	int key;
	KeyEventType type;
};

struct MouseEvent
{
	MouseEvent(double x, double y, MouseEventType t, int k = -1) : key(k), type(t), x(x), y(y) {}
	~MouseEvent() {}
	double x, y;
	int key;
	MouseEventType type;
};