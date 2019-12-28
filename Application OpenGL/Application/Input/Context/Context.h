#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Action.h"
#include "Range.h"
#include "State.h"

#include <GLFW/glfw3.h>

class Context
{
public:
	enum class MapType {
		key,
		mouse_button,
		count
	};

	Context() 
		: _maps()
	{
		_maps[size_t(MapType::key)] = std::make_unique<std::vector<std::unique_ptr<InputTypeKey>>>(GLFW_KEY_LAST + 1);
		_maps[size_t(MapType::mouse_button)] = std::make_unique<std::vector<std::unique_ptr<InputTypeKey>>>(GLFW_MOUSE_BUTTON_LAST + 1);
	}

	virtual void handle_key_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events) 
	{
		handle_events(events, MapType::key);
	}

	virtual void handle_mouse_button_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events) 
	{
		handle_events(events, MapType::mouse_button);
	}

	void attempt_execute_events() {
		for (auto& a : *_maps[size_t(MapType::key)])
			if (a)
				a->attempt_execute();
		for (auto& a : *_maps[size_t(MapType::mouse_button)])
			if (a)
				a->attempt_execute();
	}

	template<class inputtype, class cmd, typename ...Args>
	void map_key(int key, Args... args)
	{
		_maps[size_t(MapType::key)]->at(key) = std::make_unique<inputtype>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)));
	}

	template<class inputtype, class cmd, typename ...Args>
	void map_mouse(int key, Args... args)
	{
		_maps[size_t(MapType::mouse_button)]->at(key) = std::make_unique<inputtype>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)));
	}

protected:
	std::array<std::unique_ptr<std::vector<std::unique_ptr<InputTypeKey>>>, size_t(MapType::count)> _maps;

private:
	void handle_events(std::unique_ptr<std::vector<std::unique_ptr<KeyEvent>>>& events, MapType maptype)
	{
		int i = 0;

		while (i < events->size())
		{
			int key = events->at(i)->get_key();
			KeyEventType type = events->at(i)->get_type();

			if (!_maps[size_t(maptype)]->at(key))
			{
				i++;
				continue;
			}

			if (type == KeyEventType::key_pressed)
				_maps[size_t(maptype)]->at(key)->activate();
			else if (type == KeyEventType::key_released)
				_maps[size_t(maptype)]->at(key)->deactivate();

			events->erase(events->begin() + i);
		}
	}
};