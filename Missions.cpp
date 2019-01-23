#include "Missions.h"
#include "Point.h"
#include "TheSnakesGame.h"
#include<iostream>


void Missions::createMissions()
{
	int code;
	string dummy;
	string question;
	int min, max;
	int index = 0;
	ifstream file("bankMissions.txt");
	if (!file.is_open())
	{
		setTextColor(LIGHTCYAN);
		gotoxy(2, 0);
		for (int i = 0; i<79; i++)
			cout << " ";
		gotoxy(2, 0);
		cout << "The file can not be opened!";
	}
	file >> size;
	missions = new Questions*[size];
	while (!file.eof())
	{
		file >> code;
		getline(file, dummy);
		getline(file, question);
		file >> min;
		file >> max;
		switch (code)
		{
		case 1:
			missions[index] = new QPrime();
			missions[index]->setDetails(question, min, max);
			break;
		case 2:
			missions[index] = new QSquare();
			missions[index]->setDetails(question, min, max);
			break;
		case 3:
			missions[index] = new QIsDivide();
			missions[index]->setDetails(question, min, max);
			break;
		case 4:
			missions[index] = new QPalindrome();
			missions[index]->setDetails(question, min, max);
			break;
		case 5:
			missions[index] = new QExercise();
			missions[index]->setDetails(question, min, max);
			break;
		}
		index++;
	}
	file.close();
}


int Missions:: printMission(int index)
{
	index = rand() % size;
	replayIndex = index;
	missions[index]->print();
	return index;
}

bool Missions::isRightAnswer(int num, int index)
{
	return (missions[index]->IsRightAnswer(num));
}


int Missions::printReplayMission()
{
	missions[replayIndex]->print();
	return replayIndex;
}