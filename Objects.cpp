#include "Objects.h"
#include "TheSnakesGame.h"

void Objects::move(int indexMission, Missions &mission)
{
	this->getPoint()->draw(' ');
	this->getTheGame()->updateBoard(' ', this->getPoint()->getX(), this->getPoint()->getY());
	if (this->getIsDirectionChanged())
	{
		if (this->getPoint()->getY() == 1)//the object got to the top wall
		{
			this->setDirection(1);//turn down
		}
		else if (this->getPoint()->getY() == 19)//the object got to the lower wall
		{
			this->setDirection(0);//turn up
		}
		else if (this->getPoint()->getX() == 1)//the object got to the left wall
		{
			this->setDirection(3);//turn right
		}
		else if (this->getPoint()->getX() == 78)//the object got to the right wall
		{
			this->setDirection(2);//turn left
		}
	}
	this->getPoint()->move(this->getDirection());
	this->getTheGame()->updateBoard(this->getShape(), this->getPoint()->getX(), this->getPoint()->getY());
	setTextColor(this->getColor());
	this->getPoint()->draw(this->getShape());
}



int Objects::checkHits(int countNumbers, int *indexMission, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	if (this->getTheGame()->isSnake(this->getPoint()->next(this->getDirection()), '#'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
			this->getPoint()->draw(' ');
			this->getTheGame()->updateBoard(' ', this->getPoint()->getX(), this->getPoint()->getY());
			return HITSNAKE2;//hit snake2
	}

	else if (this->getTheGame()->isSnake(this->getPoint()->next(this->getDirection()), '@'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
			this->getPoint()->draw(' ');
			this->getTheGame()->updateBoard(' ', this->getPoint()->getX(), this->getPoint()->getY());
			return HITSNAKE1;//hit snake1
	}
	else if (isNumber())
	{
		
		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		return HITNUMBER;//hit a number
	}
	else if (this->getShape() == '$')
	{
		if (this->getTheGame()->isBullet(this->getPoint()->next(this->getDirection())))
		{
			this->getTheGame()->updateBoard(' ', this->getPoint()->next(this->getDirection()).getX(), this->getPoint()->next(this->getDirection()).getY());
			this->setOnBoard(false);
		}
	}
	
	return HITNOTHING;//did not hit anything
}



bool Objects::isNumber()
{
	int num;

	if (this->getTheGame()->isNumber(this->getPoint()->next(this->getDirection())))
	{
		this->getTheGame()->removeNumberFromBoard(this->getPoint()->next(this->getDirection()), num);
		return true;
	}
	return false;//did not hit a number
}



void Objects::checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission, int countNumbers, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	int pause;
	if (this->getOnBoard())
	{
		pause = checkHits(countNumbers, &indexMission, mission, isGameOver1, isGameOver2, countKey);
		switch (pause)
		{
		case HITSNAKE1:
			*stopSnake1 = true;
			break;
		case HITSNAKE2:
			*stopSnake2 = true;
			break;

		default:
			break;
		}
		move(indexMission, mission);
	}
}


void Objects::removeObject(Point p)
{
	p.draw(' ');
	this->getTheGame()->updateBoard(' ', p.getX(), p.getY());
}

void Objects::appearance(Point p)
{
	p.draw(this->getShape());
	this->getTheGame()->updateBoard(this->getShape(), p.getX(), p.getY());
	this->setOnBoard(true);
}