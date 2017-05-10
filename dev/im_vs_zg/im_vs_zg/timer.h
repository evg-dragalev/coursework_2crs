#pragma once


class Timer {
	int* piTicks;
	double* pdTickLength;
public:
	static const int MAX_TICKS_AMOUNT;
	static const double START_TICKS_LENGTH;
	static const double MIN_TICK_LENGTH;
	static const double DECREASE_COEF;
	Timer();
	void decreaseTickLength();
	void addTick();
	void substrTick();
	int runTick(double dTick);
	int getTicks() {
		return *piTicks;
	};
	double getTickLength() {
		return *pdTickLength;
	}
};