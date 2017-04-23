#include "headers.h"

#pragma once

struct NeckSegment {
	bool bIsEven;
	enum side spikeSide; // {LEFT, NONE, RIGHT}
	NeckSegment* next;
};

class Neck {
	NeckSegment* front;
	void setSegmentFrame(NeckSegment* a);
public:
	Neck();
	void cyclePop();
	side getCurrSpikeSide();
	side getNextSideSpike();
	side* getSpikeSeq();

};