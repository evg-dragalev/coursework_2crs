#include <fstream>
#include "headers.h"
const bool Drawer::DEBUG_OUT_ON = true;
const double Drawer::UPDATE_SCREEN_DELAY = 60;

COORD Drawer::coordDebugBufSize;
COORD Drawer::coordDebugBufDest;
COORD Drawer::coordDebugBufCoord;
SMALL_RECT Drawer::srctDebugReadWriteRect;
CHAR_INFO Drawer::chiReadedDebugMessage[CONSOLE_WIDTH];

HANDLE Drawer::hStdout;
HANDLE Drawer::hNewScreenBuffer;

CHAR_INFO Drawer::chiCrashFromLeft[133];		//7*19
CHAR_INFO Drawer::chiCrashFromLeftSpike[147];	//7*21
CHAR_INFO Drawer::chiCrashFromRight[133];		//7*19
CHAR_INFO Drawer::chiCrashFromRightSpike[147];	//7*21
CHAR_INFO Drawer::chiDigitsArr[10][6];			//2*3
CHAR_INFO Drawer::chiFrame[2958];				//34*87
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

void Drawer::initDrawerPlatform() {
	system("MODE CON: COLS=87 LINES=36");//!!!!!!!!!!!!!!!1добавить параметризацию через ширину и высоту консоли

	//Чтение тайлов
	ifstream fin("win_bins/crashFromLeft.bin", ios::in | ios::binary);
	fin.read((char*)chiCrashFromLeft, sizeof(chiCrashFromLeft));
	fin.close();

	fin.open("win_bins/crashFromLeftSpike.bin", ios::in | ios::binary);
	fin.read((char*)chiCrashFromLeftSpike, sizeof(chiCrashFromLeftSpike));
	fin.close();

	fin.open("win_bins/crashFromRight.bin", ios::in | ios::binary);
	fin.read((char*)chiCrashFromRight, sizeof(chiCrashFromRight));
	fin.close();

	fin.open("win_bins/crashFromRightSpike.bin", ios::in | ios::binary);
	fin.read((char*)chiCrashFromRightSpike, sizeof(chiCrashFromRightSpike));
	fin.close();

	fin.open("win_bins/digitsArr.bin", ios::in | ios::binary);
	fin.read((char*)chiDigitsArr, sizeof(chiDigitsArr));
	fin.close();

	fin.open("win_bins/frame.bin", ios::in | ios::binary);
	fin.read((char*)chiFrame, sizeof(chiFrame));
	fin.close();

	fin.open("win_bins/gameOver.bin", ios::in | ios::binary);
	fin.read((char*)chiGameOver, sizeof(chiGameOver));
	fin.close();

	fin.open("win_bins/heroAtcBottom.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroAtcBottom, sizeof(chiHeroAtcBottom));
	fin.close();

	fin.open("win_bins/heroAtcHead.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroAtcHead, sizeof(chiHeroAtcHead));
	fin.close();

	fin.open("win_bins/heroDead.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroDead, sizeof(chiHeroDead));
	fin.close();

	fin.open("win_bins/heroDeadL.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroDeadL, sizeof(chiHeroDeadL));
	fin.close();

	fin.open("win_bins/heroDeadR.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroDeadR, sizeof(chiHeroDeadR));
	fin.close();

	fin.open("win_bins/heroLeft.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroLeft, sizeof(chiHeroLeft));
	fin.close();

	fin.open("win_bins/heroLeftAtc.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroLeftAtc, sizeof(chiHeroLeftAtc));
	fin.close();

	fin.open("win_bins/heroRight.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroRight, sizeof(chiHeroRight));
	fin.close();

	fin.open("win_bins/heroRightAtc.bin", ios::in | ios::binary);
	fin.read((char*)chiHeroRightAtc, sizeof(chiHeroRightAtc));
	fin.close();

	fin.open("win_bins/neckFrames.bin", ios::in | ios::binary);
	fin.read((char*)chiNeckFrames, sizeof(chiNeckFrames));
	fin.close();

	fin.open("win_bins/scoresFrame.bin", ios::in | ios::binary);
	fin.read((char*)chiScoresFrame, sizeof(chiScoresFrame));
	fin.close();

	fin.open("win_bins/scoresFrameGameOver.bin", ios::in | ios::binary);
	fin.read((char*)chiScoresFrameGameOver, sizeof(chiScoresFrameGameOver));
	fin.close();

	fin.open("win_bins/timeStringFull.bin", ios::in | ios::binary);
	fin.read((char*)chiTimeStringFull, sizeof(chiTimeStringFull));
	fin.close();

	fin.open("win_bins/timeStringEmpty.bin", ios::in | ios::binary);
	fin.read((char*)chiTimeStringEmpty, sizeof(chiTimeStringEmpty));
	fin.close();


	//Для дебага и ошибок
	coordDebugBufSize.X = CONSOLE_WIDTH;
	coordDebugBufSize.Y = 1;

	coordDebugBufDest.X = 0;
	coordDebugBufDest.Y = CONSOLE_HEIGHT;

	coordDebugBufCoord.X = 0;
	coordDebugBufCoord.Y = 0;

	srctDebugReadWriteRect.Top = CONSOLE_HEIGHT;
	srctDebugReadWriteRect.Left = 0;
	srctDebugReadWriteRect.Bottom = CONSOLE_HEIGHT;
	srctDebugReadWriteRect.Right = CONSOLE_WIDTH - 1;

	//Определения буферов двойной буферизации
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
		debugOut("CreateConsoleScreenBuffer"); // 
	}
}


void Drawer::debugOut(char cDebugMessage[]) {
	BOOL fSuccess;

	SetConsoleCursorPosition(hStdout, coordDebugBufDest);
	cout << cDebugMessage;

	//Копирование сообщения в доп. буфер
	fSuccess = ReadConsoleOutput(
		hStdout,
		chiReadedDebugMessage,
		coordDebugBufSize,
		coordDebugBufCoord,
		&srctDebugReadWriteRect
	);
	if (!fSuccess) {
		cout << " + debugOut rbErr";
	}
	fSuccess = WriteConsoleOutput(
		hNewScreenBuffer,
		chiReadedDebugMessage,
		coordDebugBufSize,
		coordDebugBufCoord,
		&srctDebugReadWriteRect
	);
	if (!fSuccess) {
		cout << " + debugOut wbErr";
	}

}

Drawer::Drawer() {
	phInvisibleBuffer = &hStdout;
	drawFrame();
	phInvisibleBuffer = &hNewScreenBuffer;
	drawFrame();
	SetConsoleActiveScreenBuffer(hStdout);
	phVisibleBuffer = &hStdout;
}


void Drawer::drawFrame() {
	COORD coordBufSize;
	COORD coordDestPoint;

	coordBufSize.X = 87;
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

void Drawer::drawHero(side heroSide){
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

	coordDestPoint.X = 54;
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
/*
void Drawer::drawScene(side* neckSpikesSeq, side heroPosition, int timerTicks, int scores) {
	drawTimer(timerTicks);

	drawNeck(neckSpikesSeq);

	if (heroPosition != neckSpikesSeq[3]) {
		drawHero(heroPosition);
	}
	if (heroPosition == neckSpikesSeq[3]) {
		drawGrave(neckSpikesSeq[3], heroPosition);
	}

	drawScores(1);

}
*/

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
/*
		strncpy(outString + 23 * 87 + 16, heroLeftAtc[0], 12);
		for (int i = 1; i < 9; i++) {
			strncpy(outString + (i + 23) * 87 + 16, heroLeftAtc[i], 28);
		}
		strncpy(outString + 32 * 87 + 16, heroLeftAtc[9], 15);
*/
		if (neckCurrSeg == RIGHT) {
			coordBufSize.X = 21;
			coordBufSize.Y = 7;

			coordDestPoint.X = 44;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromLeftSpike);

//			for (int i = 0; i < 7; i++) {
//				strncpy(outString + (i + 25) * 87 + 44, CrashFromLeftSpike[i], 21);
//			}
		}
		else {
			coordBufSize.X = 19;
			coordBufSize.Y = 7;

			coordDestPoint.X = 44;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromLeft);
//			for (int i = 0; i < 7; i++) {
//				strncpy(outString + (i + 25) * 87 + 44, CrashFromLeft[i], 19);
//			}
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
/*
		strncpy(outString + 23 * 87 + 56, heroRightAtc[0], 8);
		for (int i = 1; i < 9; i++) {
			strncpy(outString + (i + 23) * 87 + 40, heroRightAtc[i], 28);
		}
		strncpy(outString + 32 * 87 + 52, heroRightAtc[9], 15);
*/
		if (neckCurrSeg == LEFT) {
			coordBufSize.X = 21;
			coordBufSize.Y = 7;

			coordDestPoint.X = 19;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromRightSpike);

//			for (int i = 0; i < 7; i++) {
//				strncpy(outString + (i + 25) * 87 + 19, CrashFromRightSpike[i], 21);
//			}
		}
		else {
			coordBufSize.X = 19;
			coordBufSize.Y = 7;

			coordDestPoint.X = 21;
			coordDestPoint.Y = 25;
			writeToConsole(coordDestPoint, coordBufSize, chiCrashFromRight);

//			for (int i = 0; i < 7; i++) {
//				strncpy(outString + (i + 25) * 87 + 21, CrashFromRight[i], 19);
//			}
		}
	 }
}

void Drawer::updateScreen() {
	PHANDLE phBuf;

	phBuf = phVisibleBuffer;
	phVisibleBuffer = phInvisibleBuffer;
	phInvisibleBuffer = phBuf;

	Sleep(UPDATE_SCREEN_DELAY);
	if (!SetConsoleActiveScreenBuffer(*phVisibleBuffer))
		cout << "SetConsoleActiveScreenBuffer";
}

Drawer::~Drawer() {
	if (!SetConsoleActiveScreenBuffer(hStdout))
	cout << "SetConsoleActiveScreenBuffer";
}