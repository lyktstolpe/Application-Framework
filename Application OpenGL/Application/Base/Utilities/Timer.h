#ifndef TIMER_H
#define TIMER_H

#pragma once

#include <chrono>

class Timer
{
private:
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<double, std::ratio<1> > second;

	std::chrono::time_point<clock> m_beg;

public:
	Timer() : m_beg(clock::now())
	{	}

	void reset()
	{
		m_beg = clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second> (clock::now() - m_beg).count();
	}
};

#endif