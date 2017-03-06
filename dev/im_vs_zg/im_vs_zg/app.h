#pragma once
#include "headers.h"

class App {
	Neck neck;
	Timer timer;
	bool iHeroPosition; //true - справа, false - слева
	int iScores;
public:
	App();
	void runSession();
	void chopLeft();
	void chopRight();
	void draw();
};