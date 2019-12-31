#pragma once

#include "Context_Base.h"

class Context_cursor_disabled : public Context
{
public:
	Context_cursor_disabled();

	void handle_mouse_events(std::unique_ptr<std::vector<MouseEvent>>& events);
	void attempt_invoke();

	void init_core();
	void cleanup_core();

	template<class inputtype, class cmd, typename ...Args>
	void map_mouse(int key, Args ...args)
	{
		_buttonmap[key] = std::make_unique<inputtype>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)));
	}

	template<class cmd, typename ...Args>
	void map_mouse_x(Args ...args)
	{
		_mousexmap = std::make_unique<cmd>(std::forward<Args>(args)...);
	}

	template<class cmd, typename ...Args>
	void map_mouse_y(Args ...args)
	{
		_mouseymap = std::make_unique<cmd>(std::forward<Args>(args)...);
	}

private:
	std::array<std::unique_ptr<Invoker>, GLFW_MOUSE_BUTTON_LAST + 1> _buttonmap;
	std::unique_ptr<WeightedCommand> _mousexmap;
	std::unique_ptr<WeightedCommand> _mouseymap;
};

