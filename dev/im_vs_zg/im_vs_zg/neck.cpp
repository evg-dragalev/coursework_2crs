#include "headers.h"
const int Neck::NECK_SEGM_AMOUNT = 5;
const int Neck::VISIBLE_NECK_SEGM_AMOUNT = 4;

void Neck::setSegmentFrame(NeckSegment* a) {
	if (a->bIsEven) {
		srand(time(0)); 
		int r = rand() % 5;
		switch (r) {
		case 0:
		case 1:
			a->spikeSide = LEFT;
			break;
		case 2:
			a->spikeSide = NONE;
			break;
		case 3:
		case 4:
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
	for (int i = 0; i < NECK_SEGM_AMOUNT; i++) {
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

side Neck::getNextSpikeSide() {
	return front->next->spikeSide;
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