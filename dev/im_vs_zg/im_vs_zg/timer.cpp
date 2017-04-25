#include "headers.h"

const int Timer::MAX_TICKS_AMOUNT = 22;
const double Timer::START_TICKS_LENGTH = 1.2;

Timer::Timer() {
	iTicks = new int(MAX_TICKS_AMOUNT/2);
	dTickLength = new double(START_TICKS_LENGTH);
}

void Timer::decreaseTickLength() {
	*dTickLength -= (*dTickLength < 0.6) ? 0 : 0.1;
}

void Timer::addTick() {
	*iTicks += (*iTicks < MAX_TICKS_AMOUNT) ? 1 : 0;
}

void Timer::substrTick() {
	*iTicks -= (*iTicks > 0) ? 1 : 0;
}

int Timer::getTicks() {
	return *iTicks;
}

int Timer::runTick() {
	int keyCode = 0;
	clock_t endTickTime = clock() + *dTickLength * CLOCKS_PER_SEC;
	while (clock() < endTickTime) {
		if (_kbhit()) {
			keyCode = ((keyCode = _getch()) == 224) ? getch() : keyCode;
			if (keyCode == 27 || keyCode == 77 || keyCode == 75) break;
			keyCode = 0;
		}
	}
	return keyCode;
}



