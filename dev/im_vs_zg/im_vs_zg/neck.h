#include "headers.h"

#pragma once

struct NeckSegment {
	bool bIsEven;
	enum side spikeSide; // {LEFT, NONE, RIGHT}
	NeckSegment* next;
};

class Neck {
	static const int NECK_SEGM_AMOUNT;
	NeckSegment* front;
	void setSegmentFrame(NeckSegment* a);
public:
	static const int VISIBLE_NECK_SEGM_AMOUNT;
	Neck();
	void cyclePop();
	side getCurrSpikeSide();
	side getNextSpikeSide();
	side* getSpikeSeq();

};