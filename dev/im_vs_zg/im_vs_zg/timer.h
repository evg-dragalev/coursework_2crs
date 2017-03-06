#pragma once


class Timer {
	int* ticks;
	double* tickLength;
public:
	static const int MAX_TICKS_AMOUNT;
	static const double START_TICKS_LENGTH;
	Timer();
	void DecreaseTickLength();
	void AddTick();
	void SubstrTick();
	int GetTicks();
	int RunTick();
};