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

void checkGameOver(int scores) {
	Drawer drawer;
	side neck[4] = { LEFT, NONE, RIGHT, NONE };
	drawer.drawScene(neck, LEFT, 16, 200);
	drawer.drawGameOver(scores);
	drawer.updateScreen();
}

void checkDrawer() {
	Drawer drawer;
	Neck neck;

	drawer.drawTimer(15);
	drawer.drawNeck(neck.getSpikeSeq());
	drawer.drawScores(0);
	drawer.drawHero(LEFT);
	drawer.updateScreen();
}

int main() {
//	checkNeck();
//	checkGameOver(200);
//	checkDrawer();
	system("MODE CON: COLS=88 LINES=35");
	Session session;
	session.run();

	_getch();
	
}