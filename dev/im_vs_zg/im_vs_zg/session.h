#pragma once
#include "headers.h"
#include "drawer.h"

class Session {
	Drawer* drawer;
	Neck* neck;
	Timer* timer;
	side heroPosition; 
	int iScores;
public:
	Session();
	bool chopResult(side chopSide); //���������� true ���� �������, ����� false
	void run();
	void restart();
};