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
	bool chopResult(side chopSide); //возвращает true если успешно, иначе false
	void run();
};