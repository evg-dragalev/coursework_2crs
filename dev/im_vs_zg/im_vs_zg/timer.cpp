#include "headers.h"

const int Timer::MAX_TICKS_AMOUNT = 22;
const double Timer::START_TICKS_LENGTH = 1.2;

Timer::Timer() {
	ticks = new int(MAX_TICKS_AMOUNT/2);
	tickLength = new double(START_TICKS_LENGTH);
}

void Timer::DecreaseTickLength() {
	*tickLength -= (*tickLength < 0.6) ? 0 : 0.1;
}

void Timer::AddTick() {
	*ticks += (*ticks < MAX_TICKS_AMOUNT) ? 1 : 0;
}

void Timer::SubstrTick() {
	*ticks -= (*ticks > 1) ? 1 : 0;
}

int Timer::GetTicks() {
	return *ticks;
}

int Timer::RunTick() {
	int keyCode = 0;
	clock_t endTickTime = clock() + *tickLength * CLOCKS_PER_SEC;
	while (clock() < endTickTime) {
		if (kbhit()) {
			keyCode = ((keyCode = getch()) == 224) ? getch() : keyCode;
			if (keyCode == 27 || keyCode == 77 || keyCode == 75) break;
			keyCode = 0;
		}
	}
	return keyCode;
}



