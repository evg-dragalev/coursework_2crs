#pragma once
#include "headers.h"

class Drawer {
public:
	static void initDrawerPlatform();
	static void debugOut(char cDebugMessage[]);
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

	static const bool DEBUG_OUT_ON;
	static const int CONSOLE_WIDTH = 87; //Важно! При переопределении изменить размер
	static const int CONSOLE_HEIGHT = 35;

	//Для дебага и ошибок
	static COORD coordDebugBufSize;
	static COORD coordDebugBufDest;
	static COORD coordDebugBufCoord;
	static SMALL_RECT srctDebugReadWriteRect;
	static CHAR_INFO chiReadedDebugMessage[CONSOLE_WIDTH];

	//Для двойной буферизации
	PHANDLE phVisibleBuffer;
	PHANDLE phInvisibleBuffer;
	static HANDLE hStdout;
	static HANDLE hNewScreenBuffer;
	static const double UPDATE_SCREEN_DELAY;
	
	//Тайлы
	static CHAR_INFO chiCrashFromLeft[133];			//7*19
	static CHAR_INFO chiCrashFromLeftSpike[147];	//7*21
	static CHAR_INFO chiCrashFromRight[133];		//7*19
	static CHAR_INFO chiCrashFromRightSpike[147];	//7*21
	static CHAR_INFO chiDigitsArr[10][6];			//2*3
	static CHAR_INFO chiFrame[2958];				//34*87
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
		bool fSuccess;
		SMALL_RECT srctOutRect;
		COORD coordBufCoord;

		srctOutRect.Top = coordDestPoint.Y;
		srctOutRect.Left = coordDestPoint.X;
		srctOutRect.Bottom = srctOutRect.Top + coordBufSize.Y - 1;
		srctOutRect.Right = srctOutRect.Left + coordBufSize.X - 1;

		coordBufCoord.X = 0;
		coordBufCoord.Y = 0;

		fSuccess = WriteConsoleOutput(
			*phInvisibleBuffer,
			chiTile,
			coordBufSize,
			coordBufCoord,
			&srctOutRect
		);

		if (!fSuccess) {
			//Добавить обработчик
		}
	}

	char outString[3046];//35*87+1
	char timeStrings[2][23] = {
		"______________________",
		"\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"
	};
	const char scoresFrameTileC[4][13] = {
		"\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
		"\xB3          \xB3",
		"\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9",
		"\xBF scrores: \xDA"
	};
	const char digits[10][3][3] = {
		{//0
		 "\xC9\xBB",
		 "\xBA\xBA",
		 "\xC8\xBC"
		},
		{//1
		 " \xBB",
		 " \xBA",
		 " \xCA"
		},
		{//2
		 "\xC9\xBB",
		 "\xC9\xBC",
		 "\xC8\xBC",
		},
		{//3
		 "\xC9\xBB",
		 " \xB9",
		 "\xC8\xBC"
		},
		{//4
		 "\xBB\xC9",
		 "\xC8\xB9",
		 " \xCA"
		},
		{//5
		 "\xC9\xBB",
		 "\xC8\xBB",
		 "\xC8\xBC"
		},
		{//6
		 "\xC9\xBB",
		 "\xCC\xBB",
		 "\xC8\xBC"
		},
		{//7
		 "\xC9\xBB",
		 " \xBA",
		 " \xCA"
		},
		{//8
		 "\xC9\xBB",
		 "\xCC\xB9",
		 "\xC8\xBC"
		},
		{//9
		 "\xC9\xBB",
		 "\xC8\xB9",
		 "\xC8\xBC"
		}

	};
	const char heroLeftTile[9][18] = {
		"  __    _/^\\_    ",
		" /  \\  /_____\\   ",
		" || |  | = = |   ",
		" || | _\\##^##/_  ",
		" || |/  #####  \\ ",
		" |__||   ###   | ",
		"  ][ __________/ ",
		"     /         \\ ",
		"     |____|____| "
	};
	const char heroRightTile[9][18] = {
		"    _/^\\_    __  ",
		"   /_____\\  /  \\ ",
		"   | = = |  | || ",
		"  _\\##^##/_ | || ",
		" /  #####  \\| || ",
		" |   ###   ||__| ",
		" \\__________ ][  ",
		" /         \\     ",
		" |____|____|     "
	};
	const char heroLeftAtcTile[10][29] = {
		"       _/^\\_",
		"      /_____\\    ><><><>    ",
		"      | o o |   /<><>       ",
		"     _\\##^##/_  <>  .,      ",
		"    /  #####  \\ \\<\"<;',:, . ",
		"    |   ###   |  \\,\\\\'\\\"\\,_'",
		"    \\____---=============>_>",
		"    /         \\  ///'/;//.; ",
		"    |____|____| \\<\".',':    ",
		"               ",
	};
	const char heroRightAtcTile[10][29] = {
		"_/^\\_   ",
		"    <><><><    /_____\\      ",
		"        ><>\\   | o o |      ",
		"      ,. ><>  _\\##^##/_     ",
		" . ,:,';>\">/ /  #####  \\    ",
		"'_,/\"/'//,/  |   ###   |    ",
		"<_<=============---____/    ",
		" ;.\\\\;\\'\\\\\\  /         \\    ",
		"    :','.\">/ |____|____|    ",
		"                "
	};
	const char CrashFromRight[7][20] = {
		"     .     /<><> . ",
		".  \" -; , '<;   ,  ",
		"   -. , \"._/,\"-, ' ",
		"      ;'.-  _  '-  ",
		"      - . _   ;    ",
		"    ; , ' -<>  .-' ",
		"  , -   :  \\<>     "
	};
	const char CrashFromRightSpike[7][22] = {
		"       ._ /--/<><> . ",
		"  . _\"/-;/,/'<;   ,  ",
		"  _/ -./,/\"._/,\"-, ' ",
		" <_<<<<<;'.-  _  '-  ",
		"   \\__\\\\-\\.\\_   ;    ",
		"      ;_,\\'\\-<>  .-' ",
		"    , -   :--\\\\>     "
	};
	const char CrashFromLeft[7][20] = {
		" .  ><>\\     .     ",
		"  ,   ;>' , ;- \"  .",
		" ' ,-\",\\_.\" , .-   ",
		"  -'  _  -.';      ",
		"    ;   _ . -      ",
		" '-.  <>- ' , ;    ",
		"    ></   :   - ,  "
	};
	const char CrashFromLeftSpike[7][22] = {
		" .  ><>\\--\\ _.       ",
		"  ,   ;>'\\,\\;-\\\"_ .  ",
		" ' ,-\",\\_.\"\\,\\.- \\_  ",
		"  -'  _  -.';>>>>>_> ",
		"    ;   _/./-//__/   ",
		" '-.  <>-/'/,_;      ",
		"    ><//--:   - ,    "
	};

	const char heroDeadLTile[6][12] = {
		"_/  __/// \\",
		"_<_|  |_   ",
		" |_    _| /",
		"   |  |\\\\\\<",
		" __|  |__-\\",
		"/  ----  \\ "
	};

	const char heroDeadRTile[6][12] = {
		"/ \\\\\\__  \\_",
		"   _|  |_>_",
		"\\ |_    _| ",
		">///|  |   ",
		"/-__|  |__ ",
		" /  ----  \\"
	};

	const char neckFramesTiles[3][8][53] = {
		{
			"           __/--/<><>           ><>\\                ",
			"        __/  ///<>                <>                ",
			"      _/  ///// \\<>             ><>/                ",
			"    -<_<<<<<<<   ><><><    ><><><><                 ",
			"       \\__\\\\\\\\\\ /<><>           ><>\\                ",
			"          \\__\\\\\\<>                <>                ",
			"             \\--\\<>             ><>/                ",
			"                 ><><><>    <><><><                 "
		},
		{
			"                /<><>           ><>\\                ",
			"                <>                <>                ",
			"                \\<>             ><>/                ",
			"                 ><><><    ><><><><                 ",
			"                /<><>           ><>\\                ",
			"                <>                <>                ",
			"                \\<>             ><>/                ",
			"                 ><><><>    <><><><                 "
		},
		{
			"                /<><>           ><>\\--\\__           ",
			"                <>                <>\\\\\\  \\__        ",
			"                \\<>             ><>/ \\\\\\\\\\  \\_      ",
			"                 ><><><    ><><><><   >>>>>>>_>-    ",
			"                /<><>           ><>\\ /////__/       ",
			"                <>                <>///__/          ",
			"                \\<>             ><>/--/             ",
			"                 ><><><>    <><><><                 "
		}
	};
	const char frameArr[4][88] = {
		"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9time:______________________\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n",
		"\xBA                                                                                    \xBA\n",
		"\xC8\xCD\xCD\xCD\xCD\xCD\xB9 Esc to restart \xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9 -> hit right \xCC\xCD\xB9 <- hit left \xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n",
		"                                                                                       "
	};
	const char gameOverFrame[19][60] = {
		"\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
		"\xB3                                                         \xB3",
		"\xB3  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xB3",
		"\xB3  \xBA         \xBA  \xBA         \xBA  \xBA            \xBA  \xBA         \xBA  \xB3",
		"\xB3  \xBA  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xBA  \xC9\xCD\xCD\xCD\xBB  \xBA  \xBA  \xC9\xCD\xBB  \xC9\xCD\xBB  \xBA  \xBA  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xB3",
		"\xB3  \xBA  \xBA \xC9\xCD\xCD\xCD\xCD\xBB  \xBA  \xC8\xCD\xCD\xCD\xBC  \xBA  \xBA  \xBA \xBA  \xBA \xBA  \xBA  \xBA  \xC8\xCD\xCD\xCD\xCD\xBB    \xB3",
		"\xB3  \xBA  \xBA \xC8\xCD\xBB  \xBA  \xBA  \xC9\xCD\xCD\xCD\xBB  \xBA  \xBA  \xBA \xBA  \xBA \xBA  \xBA  \xBA  \xC9\xCD\xCD\xCD\xCD\xBC    \xB3",
		"\xB3  \xBA  \xC8\xCD\xCD\xCD\xBC  \xBA  \xBA  \xBA   \xBA  \xBA  \xBA  \xBA \xBA  \xBA \xBA  \xBA  \xBA  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xB3",
		"\xB3  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xC8\xCD\xCD\xBC   \xC8\xCD\xCD\xBC  \xC8\xCD\xCD\xBC \xC8\xCD\xCD\xBC \xC8\xCD\xCD\xBC  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xB3",
		"\xB3                                                         \xB3",
		"\xB3  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xBB    \xC9\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xB3",
		"\xB3  \xBA         \xBA  \xBA   \xBA    \xBA   \xBA  \xBA         \xBA  \xBA         \xBA  \xB3",
		"\xB3  \xBA  \xC9\xCD\xCD\xCD\xBB  \xBA  \xC8\xBB  \xC8\xBB  \xC9\xBC  \xC9\xBC  \xBA  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xBA  \xC9\xCD\xCD\xCD\xBB  \xBA  \xB3",
		"\xB3  \xBA  \xBA   \xBA  \xBA   \xC8\xBB  \xC8\xBB\xC9\xBC  \xC9\xBC   \xBA  \xC8\xCD\xCD\xCD\xCD\xBB    \xBA  \xC8\xCD\xCD\xCD\xBC  \xBA  \xB3",
		"\xB3  \xBA  \xBA   \xBA  \xBA    \xC8\xBB  \xC8\xBC  \xC9\xBC    \xBA  \xC9\xCD\xCD\xCD\xCD\xBC    \xBA  \xC9\xCD\xBB  \xCB\xCD\xBC  \xB3",
		"\xB3  \xBA  \xC8\xCD\xCD\xCD\xBC  \xBA     \xC8\xBB    \xC9\xBC     \xBA  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBB  \xBA  \xBA \xBA  \xC8\xCD\xCD\xBB \xB3",
		"\xB3  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC      \xC8\xCD\xCD\xCD\xCD\xBC      \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC  \xC8\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xB3",
		"\xB3                                                         \xB3",
		"\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"
	};
};