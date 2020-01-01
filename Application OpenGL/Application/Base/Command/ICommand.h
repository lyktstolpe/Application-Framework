#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

class Application;
class IApplicationState;

namespace Command
{
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void execute() = 0;
	};  
}

#endif