#include "Bullet.h"
#include "TheSnakesGame.h"


void Bullet::move(int indexMission, Missions &mission)
{
		bullet.draw(' ');
		theGame->updateBoard(' ', bullet.getX(), bullet.getY());
		bullet.move(direction);
		theGame->updateBoard(shape, bullet.getX(), bullet.getY());
		setTextColor(color);
		bullet.draw(shape);
}

int Bullet::checkHits(int countNumbers, int *indexMission, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	if (theGame->isSnake(bullet.next(direction), '#'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
		if (snakeShape == '#')
		{
			bullet.draw(' ');
			theGame->updateBoard(' ', bullet.getX(), bullet.getY());
			onBoard = false;
			return HITSNAKE;//the bullet hit its snake
		}
		else
		{

			bullet.draw(' ');
			theGame->updateBoard(' ', bullet.getX(), bullet.getY());
			onBoard = false;
			return HITOTHERSNAKE;//the bullet hit the other snake
		}

	}

	else if (theGame->isSnake(bullet.next(direction), '@'))
	{
		PlaySound(L"Ci1asteroiddestroy.wav", NULL, SND_FILENAME | SND_ASYNC);
		if (snakeShape == '@')
		{
			bullet.draw(' ');
			theGame->updateBoard(' ', bullet.getX(), bullet.getY());
			onBoard = false;
			return HITSNAKE;//the bullet hit its snake
		}
		else
		{

			bullet.draw(' ');
			theGame->updateBoard(' ', bullet.getX(), bullet.getY());
			onBoard = false;

			return HITOTHERSNAKE;//the bullet hit the other snake
		}

	}
	else if (isNumberBullet())
	{
		bullet.draw(' ');
		theGame->updateBoard(' ', bullet.getX(), bullet.getY());
		onBoard = false;
		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		return HITNUMBER;//the bullet hit a number- the bullet did not hit any snake
	}
	else if (theGame->isFlyingLines(bullet.next(direction))) 
	{
		bullet.draw(' ');
		theGame->updateBoard(' ', bullet.getX(), bullet.getY());
		onBoard = false;

		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		return HITFLYINGLINES;//the bullet hit a number- the bullet did not hit any snake

	}
	else if (theGame->isFlyingRows(bullet.next(direction)))
	{
		bullet.draw(' ');
		
		onBoard = false;
		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		removeObject(bullet.next(direction));
		theGame->setOnBoardFlyingsRows(false, bullet.next(direction));
		return HITFLYINGROWS;//the bullet hit a number- the bullet did not hit any snake

	}
	else if (theGame->isEatingNumbers(bullet.next(direction)))
	{
		bullet.draw(' ');

		onBoard = false;
		PlaySound(L"Ionblaster.wav", NULL, SND_FILENAME | SND_ASYNC);
		removeObject(bullet.next(direction));
		theGame->setOnBoardEatingNumbers(false);
		return HITFLYINGROWS;//the bullet hit a number- the bullet did not hit any snake

	}
	return HITNOTHING;//the bullet did not hit anything- the bullet did not hit any snake
}


bool Bullet::isNumberBullet()
{
	int num;

	if (theGame->isNumber(bullet.next(direction)))
	{
		theGame->removeNumberFromBoard(bullet.next(direction), num);
		return true;
	}
	return false;//the bullet did not hit a number
}


