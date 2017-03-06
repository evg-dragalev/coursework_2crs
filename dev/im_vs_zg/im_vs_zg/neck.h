#pragma once

class Neck {
	struct NeckSegment{
		bool bIsEven;
		int iFrame; // -1 - шип слева, 0 - чисто, 1 - шип справа
		NeckSegment* next;
	};
	NeckSegment* front;
	void setSegmentFrame(NeckSegment a);
public:
	Neck();
	void cyclePop();
	int getFrontFrame();
};