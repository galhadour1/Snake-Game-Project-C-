#include "EatingNumbers.h"
#include "TheSnakesGame.h"


void EatingNumbers::move(int indexMission, Missions &mission)
{
	setDirection(theGame->bestWay(indexMission, mission));
	point.draw(' ');
	theGame->updateBoard(' ', point.getX(), point.getY());
	point.move(direction);
	theGame->updateBoard(shape, point.getX(), point.getY());
	setTextColor(color);
	point.draw(shape);
}

void EatingNumbers::checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission, int countNumbers, Missions &mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	int pause;
	if (this->getOnBoard())
	{
		pause = checkHits(countNumbers, &indexMission, mission, isGameOver1, isGameOver2, countKey);
		move(indexMission, mission);
	}
}





int EatingNumbers::checkHits(int countNumbers,int *indexMission, Missions &mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	if (theGame->isSnake(point.next(direction), '#'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
		theGame->removeSnake('#', isGameOver1, isGameOver2);
		theGame->startNewMission(countNumbers, indexMission, mission,countKey);
		theGame->appearanceSnake('#');
		return HITSNAKE2;//hit snake2
	}

	else if (theGame->isSnake(point.next(direction), '@'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
		theGame->removeSnake('@', isGameOver1, isGameOver2);
		theGame->startNewMission(countNumbers, indexMission, mission, countKey);
		theGame->appearanceSnake('@');
		return HITSNAKE1;//hit snake1
	}
	else if (isNumber())
	{
		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		return HITNUMBER;//hit a number
	}
	else if (theGame->isBullet(point.next(direction)))
	{
			removeObject(point);
			onBoard = false;
	}

	return HITNOTHING;//did not hit anything
}