#ifndef COMMAND_H
#define COMMAND_H

#pragma once

enum class KeyState {
	release,
	press,
};

enum class ActivationType {
	press,
	hold
};

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute() = 0;
	virtual ActivationType activation_type() = 0;
};  
#endif