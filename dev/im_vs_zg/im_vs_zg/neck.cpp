#include "headers.h"


void Neck::setSegmentFrame(NeckSegment a) {
	if (a.bIsEven) {
		srand(time(0));
		a.iFrame = rand() % 3;
	}
	else {
		a.iFrame = 0;
	}
}

Neck::Neck() {
	front = new NeckSegment;
	front->bIsEven = false;
	setSegmentFrame(*front);

	NeckSegment* pointer = front;
	for (int i = 0; i < 5; i++) {
		pointer->next = new NeckSegment(); //��������� ������
		pointer->next->bIsEven = !pointer->bIsEven; //������������� ��������
		setSegmentFrame(*(pointer->next));			//

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

int Neck::getFrontFrame() {
	return front->iFrame;
}