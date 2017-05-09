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

void Session::run() {
	drawer->drawTimer(timer->getTicks());
	drawer->drawNeck(neck->getSpikeSeq());
	drawer->drawScores(iScores);
	drawer->drawHero(heroPosition);
	drawer->updateScreen();
//	std::cout << "[Session.run]: screen updated";
	int iKeyCode;
	bool bGameOver = false;

	if ( getch() ) {
//		std::cout << "[Session.run]: in if";
		
		while (!bGameOver) {
			iKeyCode = timer->runTick(timer->getTickLength());
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
			case 27: //esc
				bGameOver = true;
				break;
			case 77: //стрелка вправо
				bGameOver = !chopResult(RIGHT);
				break;
			case 75: //стрелка влево
				bGameOver = !chopResult(LEFT);
				break;
			default:
				throw "error";
				break;
			}
		}
		drawer->drawTimer(timer->getTicks());
		drawer->drawNeck(neck->getSpikeSeq());
		drawer->drawScores(iScores);
		drawer->drawGrave(neck->getCurrSpikeSide(), heroPosition);
		drawer->drawGameOver(iScores);
		drawer->updateScreen();
	}
}
