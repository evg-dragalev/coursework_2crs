#include "headers.h"


void displayNeck(Neck neck) {
	side* spikeSeq = neck.getSpikeSeq();
	for (int i = 0; i < 4; i++) {
		std::cout << spikeSeq[i];
		std::cout << ", ";
	}
	std::cout << std::endl;
}

void checkNeck() {
	Neck neck;
	int key = 1;
	while (key != 27) {
		displayNeck(neck);
		key = ((key = _getch()) == 224) ? getch() : key;
		neck.cyclePop();
	}
}

void checkDrawer() {
	Drawer drawer;

	side neck[4] = { LEFT, NONE, RIGHT, RIGHT };

	drawer.drawFrame();
	drawer.drawNeck(neck);
	drawer.drawScores(222);
	drawer.drawTimer(15);
	drawer.drawGrave(neck[3], RIGHT);
	drawer.drawGameOver(222);
	drawer.updateScreen();
}


int main() {
	int iHighScores = 0;
	int iCurrScores;

	Drawer::updateConsoleTitle(iHighScores);
	Drawer::initDrawerPlatform();

	Session *session = new Session();
	iCurrScores = session->run();
	iHighScores = iCurrScores;

	int iKeyCode = 1;
	while (iKeyCode != ESCAPE_KEYCODE) {
		if (iKeyCode == SPACEBAR_KEYCODE) {
			session->~Session();
			Drawer::updateConsoleTitle(iHighScores);
			session = new Session();
			iCurrScores = session->run();
			if (iCurrScores > iHighScores) {
				iHighScores = iCurrScores;
			}
		}
		iKeyCode = ((iKeyCode = _getch()) == 224) ? getch() : iKeyCode;
	}

	return 0;
}