#include "headers.h"


void displayNeck(Neck neck) {
	side* spikeSeq = neck.getSpikeSeq();
	std::cout << spikeSeq[0] << " "
				<< spikeSeq[1] << " "
				<< spikeSeq[2] << " "
				<< spikeSeq[3] << std::endl;
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

int main() {
//	checkNeck();
	checkGameOver(200);


	_getch();
	
}