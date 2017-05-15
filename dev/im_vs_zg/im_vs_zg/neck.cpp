#include "headers.h"
const int Neck::NECK_SEGM_AMOUNT = 5;
const int Neck::VISIBLE_NECK_SEGM_AMOUNT = 4;

void Neck::setSegmentFrame(NeckSegment* a) {
	if (a->bIsEven) {
		srand(time(0)); 
		int r = rand() % 9;
		switch (r) {
		case 1:
		case 2:
		case 3:
		case 4:
			a->spikeSide = LEFT;
			break;
		case 0:
			a->spikeSide = NONE;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			a->spikeSide = RIGHT;
			break;
		default:
			std::cerr << "[neck.setSegmentFrame]: Something went wrong";
			break;
		}
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
	for (int i = 0; i < NECK_SEGM_AMOUNT; i++) {
		pointer->next = new NeckSegment();			//выделение памяти
		pointer->next->bIsEven = !pointer->bIsEven; //инициализация сегмента
		setSegmentFrame(pointer->next);				//инициализация сегмента

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

side* Neck::getSpikeSeq() {
	side* spikeSeq = new side[VISIBLE_NECK_SEGM_AMOUNT];
	NeckSegment *p = front;
	for (int i = VISIBLE_NECK_SEGM_AMOUNT - 1; i >= 0; i--) {
		spikeSeq[i] = p->spikeSide;
		p = p->next;
	}
	return spikeSeq;
}