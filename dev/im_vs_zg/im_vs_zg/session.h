#pragma once
#include "headers.h"

class Session {
	Neck* neck;
	Timer* timer;
	side heroPosition; 
	int iScores;
public:
	Session();
	bool chopResult(side chopSide); //���������� true ���� �������, ����� false
	void runSession();
	void draw();
	void restart();
};