#ifndef _MISSIONS_H_
#define _MISSIONS_H_
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include "Questions.h"
#include "QExercise.h"
#include "QIsDivide.h"
#include "QPalindrome.h"
#include "QPrime.h"
#include "QSquare.h"



using namespace std;

class Missions
{
	Questions** missions;
	int size;
	int replayIndex;
public:
	Missions() {
		createMissions();
	}
	void deleteMissions() {
		for (int i = 0; i < size + 1; ++i)
			delete missions[i];
	}
	void createMissions();
	int printMission(int index);
	bool isRightAnswer(int num, int index);
	int printReplayMission();

};
#endif // !_MISSIONS_H_
