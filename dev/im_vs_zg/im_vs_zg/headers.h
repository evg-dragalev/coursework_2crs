#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <map>
#include <assert.h>
#include "timer.h"
#include "neck.h"
#include "session.h"

enum side { LEFT, NONE, RIGHT };

const int SPACEBAR_KEYCODE = 32;
const int LEFTARROW_KEYCODE = 75;
const int RIGHTARROW_KEYCODE = 77;
const int ESCAPE_KEYCODE = 27;

const char HIGHSCORES_FILE[] = "hs.sc";