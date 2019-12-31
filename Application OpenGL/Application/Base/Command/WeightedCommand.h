#pragma once

#include "loguru.hpp"

class WeightedCommand
{
public:
	virtual ~WeightedCommand() = default;
	virtual void execute(double weight) = 0;
};

class PrintWeight : public WeightedCommand
{
public:
	PrintWeight() {}
	void execute(double weight)
	{
		LOG_F(INFO, "Weight: %f", weight);
	}
};