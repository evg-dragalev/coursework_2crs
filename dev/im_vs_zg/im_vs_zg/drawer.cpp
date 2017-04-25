#include "headers.h"

using namespace std;

Drawer::Drawer() {
	strncpy(outString, frame[0], 87);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			strncpy(outString + (1 + i * 8 + j) * 87, frame[1], 87);
		}
	}
	strncpy(outString + 33 * 87, frame[2], 87);
	strncpy(outString + 34 * 87, frame[3], 88);



	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           	// доступ к чтению/записи
		GENERIC_WRITE,
		0,                       	// совместно не используетс€
		NULL,                    	// атрибутов защиты нет
		CONSOLE_TEXTMODE_BUFFER,    // должен быть TEXTMODE
		NULL);                   	// зарезервирован, должен быть NULL
	if (hStdout == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		cout << "CreateConsoleScreenBuffer"; // 
	}
	// ѕр€моугольник источника.
	srctReadRect.Top = 0;    // верхний левый: строчка 0, колонка 0
	srctReadRect.Left = 0;
	srctReadRect.Bottom = 34; // нижний правый: строчка 33, колонка 86
	srctReadRect.Right = 86;

	// –азмер временного буфера равен 34 строчки x 87 колонок.

	coordBufSize.Y = 35;
	coordBufSize.X = 87;

	// ¬ерхн€€ лева€ €чейка назначени€ временного буфера равна строка 0, колонка 0.

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	// ѕр€моугольник назначени€.
	srctWriteRect.Top = 0;    // верхний левый: строка 0, колонка 0
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = 34; // нижний правый: строка 33, колонка 86
	srctWriteRect.Right = 86;
}

void Drawer::drawScores(int scores) {
	scores = scores % 1000;
	strncpy(outString + 4 * 87 + 36, scoresFrame[0], 12);
	for (int i = 0; i < 3; i++) {
		strncpy(outString + (5 + i) * 87 + 36, scoresFrame[1], 12);
		strncpy(outString + (5 + i) * 87 + 38, digits[scores/100][i], 2);
		strncpy(outString + (5 + i) * 87 + 41, digits[(scores/10)%10][i], 2);
		strncpy(outString + (5 + i) * 87 + 44, digits[scores%10][i], 2);
	}
	strncpy(outString + 8 * 87 + 36, scoresFrame[2], 12);

}

void Drawer::drawHero(side heroSide){
	if (heroSide == LEFT) {
		for (int i = 0; i < 9; i++) {
			strncpy(outString + (i + 24) * 87 + 15, heroLeft[i], 17);
		}
	}
	if (heroSide == RIGHT) {
		for (int i = 0; i < 9; i++) {
			strncpy(outString + (i + 24) * 87 + 52, heroRight[i], 17);
		}
	}
}

void Drawer::drawGrave(side heroSide) {
	if (heroSide == LEFT) {
		for (int i = 0; i < 6; i++) {
			strncpy(outString + (i + 27) * 87 + 22, heroDeadL[i], 11);
		}
	}
	if (heroSide == RIGHT) {
		for (int i = 0; i < 6; i++) {
			strncpy(outString + (i + 27) * 87 + 51, heroDeadR[i], 11);
		}
	}
}

void Drawer::drawNeck(side* neckSpikesSeq) {
	for (int i = 0; i < Neck::VISIBLE_NECK_SEGM_AMOUNT; i++) {
		for (int j = 0; j < 8; j++) {
			strncpy(outString + (1 + i * 8 + j) * 87 + 20, neckFrames[*(neckSpikesSeq + i)][j], 44);
		}
	}
}

void Drawer::drawTimer(int timerTicks) {
	strncpy(outString + 54, timeString, timerTicks);
}

void Drawer::drawGameOver(int scores) {
	for (int i = 0; i < 19; i++) {
		strncpy(outString + (4+i)*87 + 14, gameOver[i], 59);
	}

	scores = scores % 1000;
	strncpy(outString + 22 * 87 + 36, scoresFrame[3], 12);
	for (int i = 0; i < 3; i++) {
		strncpy(outString + (23 + i) * 87 + 36, scoresFrame[1], 12);
		strncpy(outString + (23 + i) * 87 + 38, digits[scores / 100][i], 2);
		strncpy(outString + (23 + i) * 87 + 41, digits[(scores / 10) % 10][i], 2);
		strncpy(outString + (23 + i) * 87 + 44, digits[scores % 10][i], 2);
	}
	strncpy(outString + 26 * 87 + 36, scoresFrame[2], 12);
}

void Drawer::drawScene(side* neckSpikesSeq, side heroPosition, int timerTicks, int scores) {
	drawTimer(timerTicks);

	drawNeck(neckSpikesSeq);

	if (heroPosition != neckSpikesSeq[3]) {
		drawHero(heroPosition);
	}
	if (heroPosition == neckSpikesSeq[3]) {
		drawGrave(heroPosition);
	}

	drawScores(1);

}

void Drawer::drawChop(side* neckSpikesSeq, side heroPosition, int timerTicks, int scores) {
	drawNeck(neckSpikesSeq);
	drawTimer(timerTicks);
	drawScores(scores);
	if (heroPosition == LEFT) {
		strncpy(outString + 23 * 87 + 16, heroLeftAtc[0], 12);
		for (int i = 1; i < 9; i++) {
			strncpy(outString + (i + 23) * 87 + 16, heroLeftAtc[i], 28);
		}
		strncpy(outString + 32 * 87 + 16, heroLeftAtc[9], 15);

		if (neckSpikesSeq[3] == RIGHT) {
			for (int i = 0; i < 7; i++) {
				strncpy(outString + (i + 25) * 87 + 44, CrashFromLeftSpike[i], 21);
			}
		}
		else {
			for (int i = 0; i < 7; i++) {
				strncpy(outString + (i + 25) * 87 + 44, CrashFromLeft[i], 19);
			}
		}
	}

	if (heroPosition == RIGHT) {
		strncpy(outString + 23 * 87 + 56, heroRightAtc[0], 8);
		for (int i = 1; i < 9; i++) {
			strncpy(outString + (i + 23) * 87 + 40, heroRightAtc[i], 28);
		}
		strncpy(outString + 32 * 87 + 52, heroRightAtc[9], 15);

		if (neckSpikesSeq[3] == LEFT) {
			for (int i = 0; i < 7; i++) {
				strncpy(outString + (i + 25) * 87 + 19, CrashFromRightSpike[i], 21);
			}
		}
		else {
			for (int i = 0; i < 7; i++) {
				strncpy(outString + (i + 25) * 87 + 21, CrashFromRight[i], 19);
			}
		}
	 }
}

void Drawer::updateScreen() {
	BOOL fSuccess;


	if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
		cout << "SetConsoleActiveScreenBuffer";

	SetConsoleCursorPosition(hStdout, {0 , 0});
	cout << outString;

	if (!SetConsoleActiveScreenBuffer(hStdout))
		cout << "SetConsoleActiveScreenBuffer";
	
	fSuccess = ReadConsoleOutput(
		hStdout,        	// экранный буфер, из которого читаем
		chiBuffer,      	// буфер, в который копируем
		coordBufSize,   	// размер колонки/строки chiBuffer
		coordBufCoord,  	// верхн€€ лева€ €чейка назначени€ в chiBuffer
		&srctReadRect); 	// источниковый пр€моугольник экранного буфера

	if (!fSuccess)
		cout << "ReadConsoleOutput Err";

	fSuccess = WriteConsoleOutput(
		hNewScreenBuffer, 	// экранный буфер, в который будем записывать
		chiBuffer,        	// буфер, из которого копируем
		coordBufSize,     	// размер колонки/строки chiBuffer
		coordBufCoord,    	// верхн€€ лева€ €чейка источника в chiBuffer
		&srctWriteRect);  	// пр€моугольник назначени€ экранного буфера
	
	if (!fSuccess)
		cout << "WriteConsoleOutput Err";

}