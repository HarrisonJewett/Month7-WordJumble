#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;


class Timer
{
	unsigned int startTime;

public:
	Timer();
	void reset();
	unsigned int getElapsedTime();
	//static void delay(const unsigned int milli)

};