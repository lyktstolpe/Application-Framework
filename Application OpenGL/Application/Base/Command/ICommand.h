#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <loguru.hpp>

class Application;

class ICommand
{
public:
	~ICommand() {}
	virtual void execute() = 0;
};  


#endif