#pragma once
#include "headers.h"

class Drawer {
public:
	Drawer();
	void drawHero(side heroSide);
	void drawGrave(side heroSide);
	void drawNeck(side* neckSpikesSeq);
	void drawTimer(int timeTicks);
	void   drawScene(side* neckSpikesSeq, side heroPosition, int timerticks, int scores);
	void   drawChop(side* neckSpikesSeq, side heroPosition, int timerticks, int scores);
	void updateScreen();
	void drawScores(int scores);
private:

	HANDLE hStdout;
	HANDLE hNewScreenBuffer;
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO chiBuffer[3046]; 		// 35*87+1 
	COORD coordBufSize;
	COORD coordBufCoord;


	char outString[3046];//35*87+1
	char timeString[23] = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
	const char scoresFrame[3][13] = {
		"\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
		"\xB3          \xB3",
		"\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"
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
		{
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
	const char heroLeft[9][18] = {
		"  __    _____    ",
		" /  \\  /_____\\   ",
		" || |  | = = |   ",
		" || | _\\##^##/_  ",
		" || |/  #####  \\ ",
		" |__||   ###   | ",
		"  ][ __________/ ",
		"     /         \\ ",
		"     |____|____| "
	};
	const char heroRight[9][18] = {
		"    _____    __  ",
		"   /_____\\  /  \\ ",
		"   | = = |  | || ",
		"  _\\##^##/_ | || ",
		" /  #####  \\| || ",
		" |   ###   ||__| ",
		" \\__________ ][  ",
		" /         \\     ",
		" |____|____|     "
	};
	const char heroLeftAtc[10][29] = {
		"       _____",
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
	const char heroRightAtc[10][29] = {
		"_____   ",
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

	const char heroDeadL[6][12] = {
		"_/  __/// \\",
		"_<_|  |_   ",
		" |_    _| /",
		"   |  |\\\\\\<",
		" __|  |__-\\",
		"/  ----  \\ "
	};

	const char heroDeadR[6][12] = {
		"/ \\\\\\__  \\_",
		"   _|  |_>_",
		"\\ |_    _| ",
		">///|  |   ",
		"/-__|  |__ ",
		" /  ----  \\"
	};

	const char neckFrames[3][8][45] = {
		{
			"       __/--/<><>           ><>\\            ",
			"    __/  ///<>               ><>            ",
			"  _/  ///// \\<>             ><>/            ",
			"-<_<<<<<<<   ><><><    ><><><><             ",
			"   \\__\\\\\\\\\\ /<><>           ><>\\            ",
			"      \\__\\\\\\<>                <>            ",
			"         \\--\\<>             ><>/            ",
			"             ><><><>    <><><><             "
		},
		{
			"            /<><>           ><>\\            ",
			"            <>                <>            ",
			"            \\<>             ><>/            ",
			"             ><><><    ><><><><             ",
			"            /<><>           ><>\\            ",
			"            <>                <>            ",
			"            \\<>             ><>/            ",
			"             ><><><>    <><><><             "
		},
		{
			"            /<><>           ><>\\--\\__       ",
			"            <>                <>\\\\\\  \\__    ",
			"            \\<>             ><>/ \\\\\\\\\\  \\_  ",
			"             ><><><    ><><><><   >>>>>>>_>-",
			"            /<><>           ><>\\ /////__/   ",
			"            <>                <>///__/      ",
			"            \\<>             ><>/--/         ",
			"             ><><><>    <><><><             "
		}
	};
	const char frame[4][88] = {
		"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9time:______________________\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n",
		"\xBA                                                                                    \xBA\n",
		"\xC8\xCD\xCD\xCD\xCD\xCD\xB9 Esc to restart \xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9 -> hit right \xCC\xCD\xB9 <- hit left \xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n",
		"                                                                                       "
	};
};