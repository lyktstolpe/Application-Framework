#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

class Application;
class ApplicationState;

namespace Command
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void execute() = 0;
	};  
}
