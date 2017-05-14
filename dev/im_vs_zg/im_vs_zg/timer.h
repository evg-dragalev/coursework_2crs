#pragma once


class Timer {
	int* piTicks;
	double* pdTickLength;
	static int MAX_TICKS_AMOUNT;
	static double START_TICKS_LENGTH;
	static double MIN_TICK_LENGTH;
	static double DECREASE_COEF;
public:
	static void init(int maxTicksAmount, double startTicksLength, double minTickLength, double decreaseCoef);

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