#include "headers.h"


void displayNeck(Neck neck) {
	side* spikeSeq = neck.getSpikeSeq();
	std::cout << spikeSeq[0] << " "
				<< spikeSeq[1] << " "
				<< spikeSeq[2] << " "
				<< spikeSeq[3] << std::endl;
}

int main() {
	
	Neck neck;
	int key = 1;
	while (key != 27) {
		displayNeck(neck);
		key = ((key = _getch()) == 224) ? getch() : key;
		neck.cyclePop();
	}

	_getch();
	
}