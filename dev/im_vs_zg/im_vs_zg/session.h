#pragma once
#include "headers.h"
#include "drawer.h"

class Session {
public:
	static const int DECREASE_POINTS_AMOUNT = 7;
	static void init(int dp[DECREASE_POINTS_AMOUNT]);

	Session();
	//Вернет количество набранных очков
	int run();
	bool chopResult(side chopSide);
	bool checkDecreaseTickScorePoint() {
		for (int i = 0; i < DECREASE_POINTS_AMOUNT; i++) {
			if (DECREASE_POINT[i] == iScores) return true;
		}
		return false;
	};
private:
	static int DECREASE_POINT[DECREASE_POINTS_AMOUNT];

	Drawer* drawer;
	Neck* neck;
	Timer* timer;
	side heroPosition; 
	int iScores;
};