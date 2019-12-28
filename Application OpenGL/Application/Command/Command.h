#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <loguru.hpp>

#include <string>

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute() = 0;
};  

class Print : public ICommand
{
public:
	Print()
		: _string("")
	{}
	Print(std::string string)
		: _string(string)
	{}

	void execute(){
		LOG_F(INFO, "%s", _string.c_str());
	}

private:
	std::string _string;
};
#endif