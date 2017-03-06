#pragma once

class Neck {
	struct NeckSegment{
		bool bIsEven;
		int iFrame; // -1 - ��� �����, 0 - �����, 1 - ��� ������
		NeckSegment* next;
	};
	NeckSegment* front;
	void setSegmentFrame(NeckSegment a);
public:
	Neck();
	void cyclePop();
	int getFrontFrame();
};