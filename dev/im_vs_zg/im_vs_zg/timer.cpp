#include "headers.h"

const int Timer::MAX_TICKS_AMOUNT = 22;
const double Timer::MIN_TICK_LENGTH = 0.002;
const double Timer::START_TICKS_LENGTH = 1.4;
const double Timer::DECREASE_COEF = 0.43;

Timer::Timer() {
	piTicks = new int(MAX_TICKS_AMOUNT/2);
	pdTickLength = new double(START_TICKS_LENGTH);
}

void Timer::decreaseTickLength() {
	*pdTickLength = (*pdTickLength < MIN_TICK_LENGTH) ? *pdTickLength : (*pdTickLength * DECREASE_COEF);
}

void Timer::addTick() {
	*piTicks += (*piTicks < MAX_TICKS_AMOUNT) ? 1 : 0;
}

void Timer::substrTick() {
	*piTicks -= (*piTicks > 0) ? 1 : 0;
}

int Timer::runTick(double dTick) {
	int keyCode = 0;
	clock_t endTickTime = clock() + dTick * CLOCKS_PER_SEC;
	while (clock() < endTickTime) {
		if (_kbhit()) {
			keyCode = ((keyCode = _getch()) == 224) ? getch() : keyCode;
			if (keyCode == ESCAPE_KEYCODE || keyCode == RIGHTARROW_KEYCODE || keyCode == LEFTARROW_KEYCODE) break;
			keyCode = 0;
		}
	}
	return keyCode;
}



