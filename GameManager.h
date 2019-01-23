#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <iostream>
#include <string>
#include <windows.h>
#include "io_utils.h"
#include "Missions.h"
//#include "TheSnakesGame.h"

using namespace std;

class GameManager
{
	const char ESC = 27; // the ESC key


public:
	bool isValidOption(char selection);
	void mainMenu();
	char Instructions();
	void SecondaryMenu(TheSnakesGame* game, int indexMission, Missions missionint , bool &pause0, bool &pause1, int &countKey, int &count, int &countNumbers);
	bool isValidOption2(char selection, TheSnakesGame* game, int indexMission, Missions mission, bool &pause0, bool &pause1, int &countKey, int &count, int &countNumbers);

	void ShowConsoleCursor(bool showFlag);
};
#endif