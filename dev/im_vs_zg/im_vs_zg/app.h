#pragma once
#include "headers.h"

class App {
	Neck neck;
	Timer timer;
	bool iHeroPosition; //true - ������, false - �����
	int iScores;
public:
	App();
	void runSession();
	void chopLeft();
	void chopRight();
	void draw();
};