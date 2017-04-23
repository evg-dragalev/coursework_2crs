#include "headers.h"

Session::Session() {
	drawer = new Drawer;
	neck = new Neck;
	timer = new Timer;
	heroPosition = LEFT;
	iScores = 0;
}


bool Session::chopResult(side chopSide) {
	if (neck->getCurrSpikeSide() == chopSide || neck->getNextSideSpike() == chopSide) {
		//Конец игры
		heroPosition = chopSide;
		return false;
	}
	else {
		heroPosition = chopSide;
		neck->cyclePop();
		iScores++;
		timer->AddTick();
		return true;
	}
}

void Session::runSession() {
	int keyCode;
	bool gameOver = false;
	while (!gameOver) {
		keyCode = timer->RunTick();
		switch (keyCode) {
		case 0: //ничего не нажато, "тик" прошел
			timer->SubstrTick();
			continue;
			break;
		case 27: //esc

			gameOver = true;
			break;
		case 77: //стрелка вправо
			gameOver = !chopResult(RIGHT);
			break;
		case 75: //стрелка влево
			gameOver = !chopResult(LEFT);
			break;
		default:
			throw "error";
			break;
		}

	}
}
