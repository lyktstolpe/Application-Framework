#pragma once

#include "Context_Base.h"

class Context_cursor_enabled : public Context
{
public:
	Context_cursor_enabled();
	~Context_cursor_enabled() {}

	void handle_mouse_events(std::unique_ptr<std::vector<MouseEvent>>& events);
	void attempt_invoke();

	void init_core();
	void cleanup_core();

	template<class inputtype, class cmd, typename ...Args>
	void map_mouse(int key, Bounds2D bounds, Args ...args)
	{
		_buttonmap[key].push_back(std::make_unique<inputtype>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)), bounds));
	}

	template<class cmd, typename ...Args>
	void map_hover(Bounds2D bounds, Args ...args)
	{
		_hovermap.push_back(std::make_unique<Vector>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)), bounds));
	}

private:
	std::array<std::vector<std::unique_ptr<Invoker>>, GLFW_MOUSE_BUTTON_LAST + 1> _buttonmap;
	std::vector<std::unique_ptr<Vector>> _hovermap;
};

