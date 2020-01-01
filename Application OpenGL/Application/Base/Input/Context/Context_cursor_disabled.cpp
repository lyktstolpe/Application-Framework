#include "Context_Cursor_disabled.h"

Context_cursor_disabled::Context_cursor_disabled()
{
}

void Context_cursor_disabled::handle_mouse_events(std::unique_ptr<std::vector<MouseEvent>>& events)
{
	for (int i = int(events->size()) - 1; i >= 0; --i)
	{
		MouseEventType type = events->at(i).type;
		glm::vec2 cursor(events->at(i).x, events->at(i).y);

		if (type == MouseEventType::moved)
		{
			if (_mousexmap)
				_mousexmap->execute(cursor.x);
			if (_mouseymap)
				_mouseymap->execute(cursor.y);
			continue;
		}

		int key = events->at(i).key;

		if (!_buttonmap[key])
			continue;

		if (type == MouseEventType::button_pressed)
			_buttonmap[key]->activate();

		if (type == MouseEventType::button_released)
			_buttonmap[key]->deactivate();

		events->erase(events->begin() + i);
	}
}

void Context_cursor_disabled::attempt_invoke()
{
	for (auto& invoker : _keymap)
		if (invoker)
			invoker->attempt_execute();
	for (auto& invoker : _buttonmap)
		if (invoker)
			invoker->attempt_execute();
}

void Context_cursor_disabled::init_core()
{
	glfwSetInputMode(_glfwwindow.lock().get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	init();
}

void Context_cursor_disabled::cleanup_core()
{
	for (auto& invoker : _buttonmap)
		invoker.reset(nullptr);
	_mousexmap.reset(nullptr);
	_mouseymap.reset(nullptr);
	Context::cleanup_core();
}
