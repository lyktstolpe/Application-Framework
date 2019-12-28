#pragma once

enum class KeyEventType {
	key_pressed,
	key_released,
	// Always last
	count
};

class KeyEvent
{
public:
	KeyEvent(int key, KeyEventType type)
		: _type(type)
		, _key(key)
	{}

	KeyEventType get_type() { return _type; }
	int get_key() { return _key; }

private:
	KeyEventType _type;
	int _key;
};