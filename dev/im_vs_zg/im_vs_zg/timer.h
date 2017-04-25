#pragma once


class Timer {
	int* iTicks;
	double* dTickLength;
public:
	static const int MAX_TICKS_AMOUNT;
	static const double START_TICKS_LENGTH;
	Timer();
	void decreaseTickLength();
	void addTick();
	void substrTick();
	int getTicks();
	int runTick();
};