#pragma once

class Neck {
	struct NeckSegment{
		bool bIsEven;
		side spikeSide; // 
		NeckSegment* next;
	};
	NeckSegment* front;
	void setSegmentFrame(NeckSegment a);
public:
	Neck();
	void cyclePop();
	side getCurrSpikeSide();
	side getNextSideSpike();

};