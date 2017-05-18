#pragma once
#include "headers.h"

class Drawer {
public:
	static void initDrawerPlatform(double updateScreenDelay);
	static void updateConsoleTitle(int iHightScores);
	static void readTile(char* str, std::streamsize count, char filepath[]);

	Drawer();
	~Drawer();
	void drawFrame();
	void drawHero(side heroSide);
	void drawGrave(side neckCurrSeg, side heroSide);
	void drawNeck(side* neckSpikesSeq);
	void drawTimer(int timeTicks);
	void drawGameOver(int scores);
	void drawChop(side neckCurrSeg, side heroPosition);
	void drawScores(int scores);
	void updateScreen();

private:
	static const int CONSOLE_WIDTH = 87; // <=999
	static const int CONSOLE_HEIGHT = 35;// <=999

	//Для двойной буферизации
	PHANDLE phVisibleBuffer;
	PHANDLE phInvisibleBuffer;
	static HANDLE hStdout;
	static HANDLE hNewScreenBuffer;
	static double UPDATE_SCREEN_DELAY;

	//Тайлы
	static CHAR_INFO chiCrashFromLeft[133];			//7*19
	static CHAR_INFO chiCrashFromLeftSpike[147];	//7*21
	static CHAR_INFO chiCrashFromRight[133];		//7*19
	static CHAR_INFO chiCrashFromRightSpike[147];	//7*21
	static CHAR_INFO chiDigitsArr[10][6];			//2*3
	static CHAR_INFO chiFrame[2924];				//34*86
	static CHAR_INFO chiGameOver[1121];				//19*59
	static CHAR_INFO chiHeroAtcBottom[15];			//15
	static CHAR_INFO chiHeroAtcHead[5];				//5
	static CHAR_INFO chiHeroDead[66];				//6*11
	static CHAR_INFO chiHeroDeadL[66];				//6*11
	static CHAR_INFO chiHeroDeadR[66];				//6*11
	static CHAR_INFO chiHeroLeft[153];				//9*17
	static CHAR_INFO chiHeroLeftAtc[224];			//8*28
	static CHAR_INFO chiHeroRight[153];				//9*17
	static CHAR_INFO chiHeroRightAtc[224];			//8*28
	static CHAR_INFO chiNeckFrames[3][416];			//8*52
	static CHAR_INFO chiScoresFrame[60];			//5*12
	static CHAR_INFO chiScoresFrameGameOver[60];	//5*12
	static CHAR_INFO chiTimeStringFull[22];			//22
	static CHAR_INFO chiTimeStringEmpty[22];		//22

	void writeToConsole(COORD coordDestPoint, COORD coordBufSize, CHAR_INFO chiTile[]) { //inline для быстродействия
		SMALL_RECT srctOutRect;
		COORD coordBufCoord;

		srctOutRect.Top = coordDestPoint.Y;
		srctOutRect.Left = coordDestPoint.X;
		srctOutRect.Bottom = srctOutRect.Top + coordBufSize.Y - 1;
		srctOutRect.Right = srctOutRect.Left + coordBufSize.X - 1;

		coordBufCoord.X = 0;
		coordBufCoord.Y = 0;

		if (!WriteConsoleOutput(
			*phInvisibleBuffer,
			chiTile,
			coordBufSize,
			coordBufCoord,
			&srctOutRect)) {
			SetConsoleCursorPosition(hStdout, { 0, CONSOLE_HEIGHT });
			std::cout << "[Drawer::writeToConsole()]:WriteConsoleOutput Err Code" << GetLastError();
		}
	}
};