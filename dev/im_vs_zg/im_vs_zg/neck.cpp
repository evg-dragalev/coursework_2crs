#include "headers.h"

void Neck::setSegmentFrame(NeckSegment* a) {
	if (a->bIsEven) {
		srand(time(0)); 
		int r = rand() % 3;
		switch (r) {
		case 0:
			a->spikeSide = LEFT;
			break;
		case 1:
			a->spikeSide = NONE;
			break;
		case 2:
			a->spikeSide = RIGHT;
			break;
		default:
			std::cerr << "[neck.setSegmentFrame]: Something went wrong";
			break;
		}
//		std::cout << "[neck.setSegmentFrame: a->spikeside] " << a->spikeSide <<" "<<r<< std::endl;
	}
	else {
		a->spikeSide = NONE;
	}
}

Neck::Neck() {
	front = new NeckSegment;
	front->bIsEven = false;
	setSegmentFrame(front);

	NeckSegment* pointer = front;
	for (int i = 0; i < 5; i++) {
		pointer->next = new NeckSegment();			//выделение памяти
		pointer->next->bIsEven = !pointer->bIsEven; //инициализация сегмента
		setSegmentFrame(pointer->next);			//инициализация сегмента

		pointer = pointer->next; 
	}
	pointer->next = front;
}

void Neck::cyclePop(){
	if (front->bIsEven) {
		setSegmentFrame(front);
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
side* Neck::getSpikeSeq() {
	side spikeSeq[4]{
		front->next->next->next->spikeSide,
		front->next->next->spikeSide,
		front->next->spikeSide,
		front->spikeSide
	};
	return spikeSeq;
}