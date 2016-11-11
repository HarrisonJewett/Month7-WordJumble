#include "Timer.h"



	Timer::Timer() { reset(); }

	void Timer::reset() { startTime = clock(); }

	unsigned int Timer::getElapsedTime() { return (clock() - startTime); }

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli) {}
	}
