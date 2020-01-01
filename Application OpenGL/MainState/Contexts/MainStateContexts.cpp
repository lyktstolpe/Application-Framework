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

	map_mouse<VectorAction, Print>(GLFW_MOUSE_BUTTON_LEFT, blquad, "Bottom Left");
	map_mouse<VectorAction, Print>(GLFW_MOUSE_BUTTON_RIGHT, brquad, "Bottom Right");
	map_mouse<VectorState, Print>(GLFW_MOUSE_BUTTON_LEFT, tlquad, "Top Left");
	map_mouse<VectorState, Print>(GLFW_MOUSE_BUTTON_RIGHT, trquad, "Top Right");

	map_hover<Vector, Print>(tlquad, "Hover: Top Left");
	map_key<State>(GLFW_KEY_TAB, get_command_change_to_state(1));
}

void Unbound::init()
{
	map_mouse_x<PrintWeight>();
	map_mouse_y<PrintWeight>();
	int mode = glfwGetInputMode(_glfwwindow.lock().get(), GLFW_CURSOR);

	map_key<Action, ToggleCursor>(GLFW_KEY_ESCAPE, _glfwwindow.lock().get());
}
