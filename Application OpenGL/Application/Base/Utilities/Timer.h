#pragma once

#include <chrono>

class Timer
{
private:
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<double, std::ratio<1> > second;

	std::chrono::time_point<clock> _beg;

public:
	Timer() : _beg(clock::now())
	{}

	void reset()
	{
		_beg = clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second> (clock::now() - _beg).count();
	}
};

