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
	bool checkDecreaseTickScorePoint() {
		return 0 == (10 - iScores)*(32 - iScores)*(62 - iScores)*(102 - iScores)*(204 - iScores)*(350 - iScores)*(650 - iScores);
	};
	bool chopResult(side chopSide); //возвращает true если успешно, иначе false
	int run(); //Вернет количество набранных очков
};