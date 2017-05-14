#include "headers.h"
#include <sstream>
using namespace std;

void init();
map<string, double> readConfig();
double getMapValue(map<string, double> cfgMap, string valName);
int readHighScore();
void saveHighScore(int hs);

int main() {
	int iHighScores = readHighScore();
	int iCurrScores;

	init();

	Session *session;

	int iKeyCode = SPACEBAR_KEYCODE;
	while (iKeyCode != ESCAPE_KEYCODE) {
		Drawer::updateConsoleTitle(iHighScores);
		if (iKeyCode == SPACEBAR_KEYCODE) {
			session = new Session();
			iCurrScores = session->run();
			if (iCurrScores > iHighScores) {
				iHighScores = iCurrScores;
			}
			session->~Session();
		}
		iKeyCode = ((iKeyCode = _getch()) == 224) ? getch() : iKeyCode;
	}

	saveHighScore(iHighScores);

	return 0;
}

void init() {
	map <string, double> cfgMap = readConfig();
	Timer::init(
		(int)getMapValue(cfgMap, "TIMER_MAX_TICKS_AMOUNT"),
		getMapValue(cfgMap, "TIMER_START_TICKS_LENGTH"),
		getMapValue(cfgMap, "TIMER_MIN_TICK_LENGTH"),
		getMapValue(cfgMap, "TIMER_DECREASE_COEF")

	);
	Drawer::initDrawerPlatform(
		getMapValue(cfgMap, "DRAWER_UPDATE_SCREEN_DELAY")
	);
	
	int decrPoints[Session::DECREASE_POINTS_AMOUNT] = {
		getMapValue(cfgMap, "SESSION_DECR_POINT1"),
		getMapValue(cfgMap, "SESSION_DECR_POINT2"),
		getMapValue(cfgMap, "SESSION_DECR_POINT3"),
		getMapValue(cfgMap, "SESSION_DECR_POINT4"),
		getMapValue(cfgMap, "SESSION_DECR_POINT5"),
		getMapValue(cfgMap, "SESSION_DECR_POINT6"),
		getMapValue(cfgMap, "SESSION_DECR_POINT7"),
	};

	Session::init(decrPoints);
}

map<string, double> readConfig() {
	map <string, double> cfgMap;
	ifstream cfgIn("settings.cfg", ios::in);
	try {
		int cycleLimit = 0;
		char tmp;
		string cfgVarName;
		double cfgVarValue;
		while (!cfgIn.eof()) {
			if (cycleLimit++ > 20) throw "Config file structure error";
			cfgIn >> cfgVarName >> tmp >> cfgVarValue;
			cfgMap.insert(pair<string, double>(cfgVarName, cfgVarValue));
		}
	}
	catch (const ifstream::failure&) {
		cout << "Error reaading/finding config file. The game will run with standart settings\n"
			<< "Press any key to continue\n";
		cfgMap.clear();
		_getch();
		return cfgMap;
	}
	catch (const char* err) {
		cout << err << ". The game will run with standart settings\n"
			<< "Press any key to continue\n";
		cfgMap.clear();
		_getch();
		return cfgMap;
	}
	return cfgMap;
}

double getMapValue(map<string, double> cfgMap, string valName) {
	if (cfgMap.find(valName) != cfgMap.end()) {
		return cfgMap.at(valName);
	}
	else {
		return 0;
	}
}

int readHighScore() {
	int hs = 0;
	ifstream hsin(HIGHSCORES_FILE, ios::binary);
	if (hsin || !hsin.eof()) {
		hsin >> hs;
	}
	hsin.close();

	return hs;
}

void saveHighScore(int hs) {
	ofstream hsout(HIGHSCORES_FILE, ios::binary);
	hsout << hs;
	hsout.close();
}