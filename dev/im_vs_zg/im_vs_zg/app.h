#include "headers.h"

#pragma once

class Application {
	static const char HIGHSCORES_FILE[];
	static const char CONFIG_FILE[];
	int iHighScores;
	Session* session;

	Application();
	~Application();
	Application(const Application&) = delete;
	Application& operator= (Application const&) = delete;

	std::map<std::string, double> readConfig();
	double getMapValue(std::map<std::string, double> cfgMap, std::string valName);
	int readHighScore();
	void saveHighScore(int hs);

public:
	static Application& Instance();
	void run();

};