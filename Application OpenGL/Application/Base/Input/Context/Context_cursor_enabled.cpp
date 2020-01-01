#include "Context_cursor_enabled.h"

Context_cursor_enabled::Context_cursor_enabled()
{

}

void Context_cursor_enabled::handle_mouse_events(std::unique_ptr<std::vector<MouseEvent>>& events)
{
	for (int i = int(events->size()) - 1; i >= 0; --i)
	{
		MouseEventType type = events->at(i).type;
		glm::vec2 cursor(events->at(i).x, events->at(i).y);

		if (type == MouseEventType::moved)
		{
			for (auto& invoker : _hovermap)
				if (invoker)
					invoker->activate(cursor);
			continue;
		}

		int key = events->at(i).key;

		if (_buttonmap[key].empty())
			continue;

		if (type == MouseEventType::button_pressed)
			for (auto& invoker : _buttonmap[key])
				if (invoker)
					invoker->activate(cursor);

		if (type == MouseEventType::button_released)
			for (auto& invoker : _buttonmap[key])
				if (invoker)
					invoker->deactivate();

		events->erase(events->begin() + i);
	}
}

void Context_cursor_enabled::attempt_invoke()
{
	for (auto& invoker : _keymap)
		if (invoker)
			invoker->attempt_execute();
	for (auto& invoker : _hovermap)
		if (invoker)
			invoker->attempt_execute();
	for (auto& vector : _buttonmap)
		for (auto& invoker : vector)
			if (invoker)
				invoker->attempt_execute();
}

void Context_cursor_enabled::init_core()
{
	glfwSetInputMode(_glfwwindow.lock().get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	init();
}

void Context_cursor_enabled::cleanup_core()
{
	for (auto& vector : _buttonmap)
	{
		for (auto& invoker : vector)
			invoker.reset(nullptr);
		vector.clear();
	}
	for (auto& invoker : _hovermap)
		invoker.reset(nullptr);
	Context::cleanup_core();
}
