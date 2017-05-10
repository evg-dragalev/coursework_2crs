#include "headers.h"

Session::Session() {
	drawer = new Drawer;
	neck = new Neck;
	timer = new Timer;
	heroPosition = LEFT;
	iScores = 0;
}

bool Session::chopResult(side chopSide) {
	heroPosition = chopSide;
	side spikeSide = neck->getCurrSpikeSide();
	if (spikeSide == heroPosition) {
		drawer->drawTimer(timer->getTicks());
		drawer->drawNeck(neck->getSpikeSeq());
		drawer->drawScores(iScores);
		drawer->drawGrave(spikeSide, heroPosition);
		drawer->updateScreen();
		return false;
	} 
	else {
		iScores++;
		timer->addTick();

		if (iScores % 5 == 0) {
			timer->decreaseTickLength();
		}
		drawer->drawTimer(timer->getTicks());
		drawer->drawNeck(neck->getSpikeSeq());
		drawer->drawScores(iScores);
		drawer->drawChop(spikeSide, heroPosition);
		drawer->updateScreen();
		neck->cyclePop();

		spikeSide = neck->getCurrSpikeSide();
		if (spikeSide == heroPosition) {
			drawer->drawTimer(timer->getTicks());
			drawer->drawNeck(neck->getSpikeSeq());
			drawer->drawScores(iScores);
			drawer->drawGrave(spikeSide, heroPosition);
			drawer->updateScreen();
			return false;
		}
		else {
			drawer->drawTimer(timer->getTicks());
			drawer->drawNeck(neck->getSpikeSeq());
			drawer->drawScores(iScores);
			drawer->drawHero(heroPosition);
			drawer->updateScreen();
			return true;
		}
	}
}

int Session::run() {
	drawer->drawTimer(timer->getTicks());
	drawer->drawNeck(neck->getSpikeSeq());
	drawer->drawScores(iScores);
	drawer->drawHero(heroPosition);
	drawer->updateScreen();

	int iKeyCode;
	bool bGameOver = false;

	//Первое нажатие
	while (true) {
		if (_kbhit()) {
			iKeyCode = ((iKeyCode = _getch()) == 224) ? getch() : iKeyCode;
			if (iKeyCode == ESCAPE_KEYCODE || iKeyCode == RIGHTARROW_KEYCODE || iKeyCode == LEFTARROW_KEYCODE) break;
			iKeyCode = 0;
		}
	}
		
	while (!bGameOver) {
		switch (iKeyCode) {
		case 0: //ничего не нажато, "тик" прошел
			if (timer->getTicks() == 0) {
				bGameOver = true;
			} 
			else {
				timer->substrTick();
				drawer->drawTimer(timer->getTicks());
				drawer->drawNeck(neck->getSpikeSeq());
				drawer->drawScores(iScores);
				drawer->drawHero(heroPosition);
				drawer->updateScreen();
			}
			break;
		case ESCAPE_KEYCODE: //esc
			bGameOver = true;
			break;
		case RIGHTARROW_KEYCODE: //стрелка вправо
			bGameOver = !chopResult(RIGHT);
			break;
		case LEFTARROW_KEYCODE: //стрелка влево
			bGameOver = !chopResult(LEFT);
			break;
		default:
			throw "error";
			break;
		}
		if (!bGameOver) iKeyCode = timer->runTick(timer->getTickLength());
	}

	drawer->drawTimer(timer->getTicks());
	drawer->drawNeck(neck->getSpikeSeq());
	drawer->drawScores(iScores);
	drawer->drawGrave(neck->getCurrSpikeSide(), heroPosition);
	drawer->drawGameOver(iScores);
	drawer->updateScreen();
	return iScores;
}
