#include "MainStateContexts.h"

void Bound::init()
{
	Bounds2D blquad = {
		glm::vec2(-1.0),
		glm::vec2(0.0)
	};
	Bounds2D brquad = {
		glm::vec2(0.0, -1.0),
		glm::vec2(1.0,  0.0)
	};
	Bounds2D tlquad = {
		glm::vec2(-1.0, 0.0),
		glm::vec2(0.0, 1.0)
	};
	Bounds2D trquad = {
		glm::vec2(0.0),
		glm::vec2(1.0)
	};

	map_mouse<VectorAction, Command::Print>(GLFW_MOUSE_BUTTON_LEFT, blquad, "Bottom Left");
	map_mouse<VectorAction, Command::Print>(GLFW_MOUSE_BUTTON_RIGHT, brquad, "Bottom Right");
	map_mouse<VectorState, Command::Print>(GLFW_MOUSE_BUTTON_LEFT, tlquad, "Top Left");
	map_mouse<VectorState, Command::Print>(GLFW_MOUSE_BUTTON_RIGHT, trquad, "Top Right");

	map_key<Action>(GLFW_KEY_A, get_command_change_to_context(1));

	map_hover<Vector, Command::Print>(tlquad, "Hover: Top Left");
	map_key<State>(GLFW_KEY_TAB, get_command_change_to_state(1));
}

void Unbound::init()
{
	map_mouse_x<Command::PrintWeight>();
	map_mouse_y<Command::PrintWeight>();
	int mode = glfwGetInputMode(_glfwwindow.lock().get(), GLFW_CURSOR);

	map_key<Action>(GLFW_KEY_A, get_command_change_to_context(0));

	map_key<Action, Command::ToggleCursor>(GLFW_KEY_ESCAPE, _glfwwindow.lock().get());
}
