#include "headers.h"


void Neck::setSegmentFrame(NeckSegment a) {
	if (a.bIsEven) {
		srand(time(0));
		a.spikeSide = (side)(rand() % 3);
	}
	else {
		a.spikeSide = side(0);
	}
}

Neck::Neck() {
	front = new NeckSegment;
	front->bIsEven = false;
	setSegmentFrame(*front);

	NeckSegment* pointer = front;
	for (int i = 0; i < 5; i++) {
		pointer->next = new NeckSegment();			//выделение памяти
		pointer->next->bIsEven = !pointer->bIsEven; //инициализация сегмента
		setSegmentFrame(*(pointer->next));			//инициализация сегмента

		pointer = pointer->next; 
	}
	pointer->next = front;
}

void Neck::cyclePop(){
	if (front->bIsEven) {
		setSegmentFrame(*front);
		front = front->next;
	}
	else {
		front = front->next;
	}
}

side Neck::getCurrSpikeSide() {
	return front->spikeSide;
}

side Neck::getNextSideSpike() {
	return front->next->spikeSide;
}