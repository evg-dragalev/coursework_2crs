#include <stdio.h>
#include "headers.h"

double Drawer::UPDATE_SCREEN_DELAY = 60;

HANDLE Drawer::hStdout;
HANDLE Drawer::hNewScreenBuffer;

CHAR_INFO Drawer::chiCrashFromLeft[133];		//7*19
CHAR_INFO Drawer::chiCrashFromLeftSpike[147];	//7*21
CHAR_INFO Drawer::chiCrashFromRight[133];		//7*19
CHAR_INFO Drawer::chiCrashFromRightSpike[147];	//7*21
CHAR_INFO Drawer::chiDigitsArr[10][6];			//2*3
CHAR_INFO Drawer::chiFrame[2924];				//34*86
CHAR_INFO Drawer::chiGameOver[1121];			//19*59
CHAR_INFO Drawer::chiHeroAtcBottom[15];			//15
CHAR_INFO Drawer::chiHeroAtcHead[5];			//5
CHAR_INFO Drawer::chiHeroDead[66];				//6*11
CHAR_INFO Drawer::chiHeroDeadL[66];				//6*11
CHAR_INFO Drawer::chiHeroDeadR[66];				//6*11
CHAR_INFO Drawer::chiHeroLeft[153];				//9*17
CHAR_INFO Drawer::chiHeroLeftAtc[224];			//8*28
CHAR_INFO Drawer::chiHeroRight[153];			//9*17
CHAR_INFO Drawer::chiHeroRightAtc[224];			//8*28
CHAR_INFO Drawer::chiNeckFrames[3][416];		//8*52
CHAR_INFO Drawer::chiScoresFrame[60];			//5*12
CHAR_INFO Drawer::chiScoresFrameGameOver[60];	//5*12
CHAR_INFO Drawer::chiTimeStringFull[22];		//22
CHAR_INFO Drawer::chiTimeStringEmpty[22];		//22

using namespace std;

void Drawer::readTile(char* str, streamsize count, char filepath[]){
	try {
		ifstream fin(filepath, ios::in | ios::binary);
		fin.seekg(0, ios::end);
		if (!fin || (long)fin.tellg() == 0) throw "Error, bin file not found or empty";
		fin.seekg(0, ios::beg);
		fin.read(str, count);
		fin.close();
	}
	catch (const iostream::failure&) {
		cout << "Error reading/finding bin files. Make sure you have win_bins catalogue in game directory, or download it from github: " << endl
			<< "https://github.com/evg-dragalev/coursework_2crs/tree/master/dev/im_vs_zg/im_vs_zg/win_bins " << endl
			<< "Press any button to quit";
		_getch();
		exit(2);
	}
	catch (const char* err) {
		cout << err << ". You can download any missing files from github: " << endl
			<< "https://github.com/evg-dragalev/coursework_2crs/tree/master/dev/im_vs_zg/im_vs_zg/win_bins " << endl
			<< "Press any button to quit";
		_getch();
		exit(3);
	}
}

void Drawer::initDrawerPlatform(double updateScreenDelay) {
	UPDATE_SCREEN_DELAY = (updateScreenDelay > 0) ? updateScreenDelay : UPDATE_SCREEN_DELAY;

	char modConCommand[30];
	snprintf(modConCommand, 30, "MODE CON: COLS=%d LINES=%d", CONSOLE_WIDTH, CONSOLE_HEIGHT);
	system(modConCommand);

	//Чтение тайлов
	readTile((char*)chiCrashFromLeft, sizeof(chiCrashFromLeft), "win_bins/crashFromLeft.bin");
	readTile((char*)chiCrashFromLeftSpike, sizeof(chiCrashFromLeftSpike), "win_bins/crashFromLeftSpike.bin");
	readTile((char*)chiCrashFromRight, sizeof(chiCrashFromRight), "win_bins/crashFromRight.bin");
	readTile((char*)chiCrashFromRightSpike, sizeof(chiCrashFromRightSpike), "win_bins/crashFromRightSpike.bin");
	readTile((char*)chiDigitsArr, sizeof(chiDigitsArr), "win_bins/digitsArr.bin");
	readTile((char*)chiFrame, sizeof(chiFrame), "win_bins/frame.bin");
	readTile((char*)chiGameOver, sizeof(chiGameOver), "win_bins/gameOver.bin");
	readTile((char*)chiHeroAtcBottom, sizeof(chiHeroAtcBottom), "win_bins/heroAtcBottom.bin");
	readTile((char*)chiHeroAtcHead, sizeof(chiHeroAtcHead), "win_bins/heroAtcHead.bin");
	readTile((char*)chiHeroDead, sizeof(chiHeroDead), "win_bins/heroDead.bin");
	readTile((char*)chiHeroDeadL, sizeof(chiHeroDeadL), "win_bins/heroDeadL.bin");
	readTile((char*)chiHeroDeadR, sizeof(chiHeroDeadR), "win_bins/heroDeadR.bin");
	readTile((char*)chiHeroLeft, sizeof(chiHeroLeft), "win_bins/heroLeft.bin");
	readTile((char*)chiHeroLeftAtc, sizeof(chiHeroLeftAtc), "win_bins/heroLeftAtc.bin");
	readTile((char*)chiHeroRight, sizeof(chiHeroRight), "win_bins/heroRight.bin");
	readTile((char*)chiHeroRightAtc, sizeof(chiHeroRightAtc), "win_bins/heroRightAtc.bin");
	readTile((char*)chiNeckFrames, sizeof(chiNeckFrames), "win_bins/neckFrames.bin");
	readTile((char*)chiScoresFrame, sizeof(chiScoresFrame), "win_bins/scoresFrame.bin");
	readTile((char*)chiScoresFrameGameOver, sizeof(chiScoresFrameGameOver), "win_bins/scoresFrameGameOver.bin");
	readTile((char*)chiTimeStringFull, sizeof(chiTimeStringFull), "win_bins/timeStringFull.bin");
	readTile((char*)chiTimeStringEmpty, sizeof(chiTimeStringEmpty), "win_bins/timeStringEmpty.bin");
	
	//Определения буферов для двойной буферизации
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           	// доступ к чтению/записи
		GENERIC_WRITE,
		0,                       	// совместно не используется
		NULL,                    	// атрибутов защиты нет
		CONSOLE_TEXTMODE_BUFFER,    // должен быть TEXTMODE
		NULL);                   	// зарезервирован, должен быть NULL
	if (hStdout == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE){
		SetConsoleCursorPosition(hStdout, { 0, CONSOLE_HEIGHT });
		cout << "[Drawer::initDrawerPlatform()]: CreateConsoleScreenBuffer Err Code - "<< GetLastError();
	}
}

void Drawer::updateConsoleTitle(int iHighScore) {
	wchar_t wcConsoleTitle[50];
	swprintf(wcConsoleTitle, L"Ilya Muromets VS Zmey Gorynych. Highscore: %d", iHighScore);
	SetConsoleTitle(wcConsoleTitle);
}

Drawer::Drawer() {
	phInvisibleBuffer = &hStdout;
	drawFrame();
	phInvisibleBuffer = &hNewScreenBuffer;
	drawFrame();

	phVisibleBuffer = &hStdout;
	SetConsoleCursorPosition(hStdout, { 0, CONSOLE_HEIGHT });
}

void Drawer::drawFrame() {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 86;
	coordBufSize.Y = 34;

	coordDestPoint.X = 0;
	coordDestPoint.Y = 0;
	writeToConsole(coordDestPoint, coordBufSize, chiFrame);	
}

void Drawer::drawScores(int scores) {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 12;
	coordBufSize.Y = 5;

	coordDestPoint.X = 36;
	coordDestPoint.Y = 4;
	writeToConsole(coordDestPoint, coordBufSize, chiScoresFrame);

	scores = scores % 1000;

	coordBufSize.X = 2;
	coordBufSize.Y = 3;

	coordDestPoint.X = 38;
	coordDestPoint.Y = 5;
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores/100]);
	
	coordDestPoint.X = 41;
	//			  .Y = 5
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores/10%10]);
	
	coordDestPoint.X = 44;
	//			  .Y = 5
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores%10]);
}

void Drawer::drawHero(side heroSide) {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 17;
	coordBufSize.Y = 9;
	
	if (heroSide == LEFT) {
		coordDestPoint.X = 15;
		coordDestPoint.Y = 24;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroLeft);
	}
	if (heroSide == RIGHT) {
		coordDestPoint.X = 52;
		coordDestPoint.Y = 24;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroRight);
	}
}

void Drawer::drawGrave(side neckCurrSeg, side heroSide) {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 52;
	coordBufSize.Y = 8;

	coordDestPoint.X = 16;
	coordDestPoint.Y = 25;
	
	writeToConsole(coordDestPoint, coordBufSize, chiNeckFrames[neckCurrSeg]);

	coordBufSize.X = 15;
	coordBufSize.Y = 1;

	coordDestPoint.X = 16;
	coordDestPoint.Y = 24;
	writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcBottom);
	coordDestPoint.X = 52;
	writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcBottom);
	
	coordBufSize.X = 11;
	coordBufSize.Y = 6;
	if (heroSide == LEFT) {
		coordDestPoint.X = 21;
		coordDestPoint.Y = 27;
		if (heroSide == neckCurrSeg) {
			writeToConsole(coordDestPoint, coordBufSize, chiHeroDeadL);
		}
		else {
			writeToConsole(coordDestPoint, coordBufSize, chiHeroDead);
		}
	}
	if (heroSide == RIGHT) {
		coordDestPoint.X = 52;
		coordDestPoint.Y = 27;
		if (heroSide == neckCurrSeg) {
			writeToConsole(coordDestPoint, coordBufSize, chiHeroDeadR);
		}
		else {

			writeToConsole(coordDestPoint, coordBufSize, chiHeroDead);
		}
	}
}

void Drawer::drawNeck(side* neckSpikesSeq) {
	COORD coordBufSize;
	COORD coordDestPoint;
	
	coordBufSize.X = 52;
	coordBufSize.Y = 8;

	coordDestPoint.X = 16;

	for (int i = 0; i < Neck::VISIBLE_NECK_SEGM_AMOUNT; i++) {
		coordDestPoint.Y = 1 + i * 8;
		writeToConsole(coordDestPoint, coordBufSize, chiNeckFrames[neckSpikesSeq[i]]);
	}
}

void Drawer::drawTimer(int timerTicks) {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordDestPoint.X = 55;
	coordDestPoint.Y = 0;

	coordBufSize.X = 22;
	coordBufSize.Y = 1;
	writeToConsole(coordDestPoint, coordBufSize, chiTimeStringEmpty);

	coordBufSize.X = timerTicks;
	writeToConsole(coordDestPoint, coordBufSize, chiTimeStringFull);
}

void Drawer::drawGameOver(int scores) {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 59;
	coordBufSize.Y = 19;

	coordDestPoint.X = 14;
	coordDestPoint.Y = 4;

	writeToConsole(coordDestPoint, coordBufSize, chiGameOver);

	coordBufSize.X = 12;
	coordBufSize.Y = 5;

	coordDestPoint.X = 36;
	coordDestPoint.Y = 22;

	writeToConsole(coordDestPoint, coordBufSize, chiScoresFrameGameOver);

	scores = scores % 1000;
	coordBufSize.X = 2;
	coordBufSize.Y = 3;

	coordDestPoint.X = 38;
	coordDestPoint.Y = 23;
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores / 100]);

	coordDestPoint.X = 41;
	//			  .Y = 23
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores / 10 % 10]);

	coordDestPoint.X = 44;
	//			  .Y = 23
	writeToConsole(coordDestPoint, coordBufSize, chiDigitsArr[scores % 10]);
}

void Drawer::drawChop(side neckCurrSeg, side heroPosition) {
	COORD coordBufSize;
	COORD coordDestPoint;
	
	if (heroPosition == LEFT) {
		coordBufSize.X = 5;
		coordBufSize.Y = 1;

		coordDestPoint.X = 23;
		coordDestPoint.Y = 23;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcHead);

		coordBufSize.X = 28;
		coordBufSize.Y = 8;

		coordDestPoint.X = 16;
		coordDestPoint.Y = 24;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroLeftAtc);

		coordBufSize.X = 15;
		coordBufSize.Y = 1;

		coordDestPoint.X = 16;
		coordDestPoint.Y = 32;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcBottom);

		if (neckCurrSeg == RIGHT) {
			coordBufSize.X = 21;
			coordBufSize.Y = 7;

			coordDestPoint.X = 44;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromLeftSpike);
		}
		else {
			coordBufSize.X = 19;
			coordBufSize.Y = 7;

			coordDestPoint.X = 44;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromLeft);
		}
	}

	if (heroPosition == RIGHT) {
		coordBufSize.X = 5;
		coordBufSize.Y = 1;

		coordDestPoint.X = 56;
		coordDestPoint.Y = 23;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcHead);

		coordBufSize.X = 28;
		coordBufSize.Y = 8;

		coordDestPoint.X = 40;
		coordDestPoint.Y = 24;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroRightAtc);

		coordBufSize.X = 15;
		coordBufSize.Y = 1;

		coordDestPoint.X = 52;
		coordDestPoint.Y = 32;
		writeToConsole(coordDestPoint, coordBufSize, chiHeroAtcBottom);

		if (neckCurrSeg == LEFT) {
			coordBufSize.X = 21;
			coordBufSize.Y = 7;

			coordDestPoint.X = 19;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromRightSpike);
		}
		else {
			coordBufSize.X = 19;
			coordBufSize.Y = 7;

			coordDestPoint.X = 21;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromRight);
		}
	 }
}

void Drawer::updateScreen() {
	PHANDLE phBuf;

	phBuf = phVisibleBuffer;
	phVisibleBuffer = phInvisibleBuffer;
	phInvisibleBuffer = phBuf;

	Sleep(UPDATE_SCREEN_DELAY);
	if (!SetConsoleActiveScreenBuffer(*phVisibleBuffer)) {
		SetConsoleCursorPosition(hStdout, { 0, CONSOLE_HEIGHT });
		cout << "[Drawer::updateScreen()]:SetConsoleActiveScreenBuffer Err";
	}
}

Drawer::~Drawer() {
	if (!SetConsoleActiveScreenBuffer(hStdout)) {
		SetConsoleCursorPosition(hStdout, { 0, CONSOLE_HEIGHT });
		cout << "[Drawer::~Drawer()]:SetConsoleActiveScreenBuffer Err";
	}
}