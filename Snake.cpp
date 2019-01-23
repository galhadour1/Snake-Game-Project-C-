#include "Snake.h"
#include"TheSnakesGame.h"
void Snake::setPosition(int y, int x)
{
	for (int i = 0; i < size; i++)
		body[i].set(x, y);

}

void Snake::move()
{
	if (theGame->isSnake(body[0].next(direction), '#'))
	{
		direction = 4;//The snake will not move
	}

	if (theGame->isSnake(body[0].next(direction), '@'))
	{
		direction = 4;//The snake will not move
	}
	
		body[size - 1].draw(' ');
		theGame->updateBoard(' ', body[size - 1].getX(), body[size - 1].getY());
		for (int i = size - 1; i >0; --i)
			body[i].set(body[i - 1].getX(), body[i - 1].getY());
		
	
		body[0].move(direction);
		theGame->updateBoard(shape, body[0].getX(), body[0].getY());

		setTextColor(color);
		body[0].draw(shape);

}

int Snake::getDirection(char key)
{
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
		{
			return i;
		}
	}
	return -1;
}


void Snake::setShape(char ch)
{
	shape = ch;
	srand((int)time(NULL));
	for (int i = 0; i < MAXBULLETS; i++)
	{
		bullet[i].setSnakeShape(shape);
		if (shape == '@')
			bullet[i].setArrowKey('z');
		else
			bullet[i].setArrowKey('n');
		bullet[i].setColor(color);
	}

}
int Snake::isNumberSnake(int indexMission,bool *isGameOver, Missions &mission)
{
	int num;

	if (theGame->isNumber(body[0].next(direction)))
	{
		theGame->removeNumberFromBoard(body[0].next(direction), num);
		if (theGame->isNumberValid(body[0].next(direction), indexMission, num, mission))
		{
			*isGameOver = biggerSnake();
			return 1;//the snake ate the right number

		}
		else
			return 0;//the snake ate the wrong number
	}

	return 2;//the snake did not eat any number
}

bool  Snake::biggerSnake()
{
	
	
	if (size != MAXSIZE)
	{
	
		size++;
		return false;
	}
	else
	{
		return true;
		
		
	}
}

void Snake::clearBullets()
{
	for (int i = 0; i < MAXBULLETS; i++)
	{
		bullet[i].setOnBoard(false);
		theGame->updateBoard(' ', bullet[i].getX(), bullet[i].getY());
		gotoxy(bullet[i].getX(), bullet[i].getY() + 3);
		cout << " ";
	}
	emptyPlace = 0;
}



void Snake::checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission, int countNumbers, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey)
{
	int pause;

	for (int i = 0; i < MAXBULLETS; i++)
	{
		if (bullet[i].getOnBoard())
		{
			pause = bullet[i].checkHits(countNumbers, &indexMission, mission, isGameOver1, isGameOver2, countKey);
			switch (pause)
			{
			case HITSNAKE:
				*stopSnake1 = true;
				break;
			case HITOTHERSNAKE:
				*stopSnake2 = true;
				numBullets++;
				break;
			case HITFLYINGROWS:
				numBullets++;
				break;
			case HITNOTHING:
				bullet[i].move(indexMission, mission);
				break;
			default:
				break;
			}
		}
	}
}

void Snake:: findEmptyPlace() {
	bool find = false;
	for (int i = 0; (i < MAXBULLETS) && (!find); i++)
		if (!bullet[i].getOnBoard())
		{
			emptyPlace = i;
			find = true;
		}
}



void Snake:: removeSnake()
{	
	for (int i = 0; i < size; i++)
	{
		body[i].draw(' ');
		theGame->updateBoard(' ', body[i].getX(), body[i].getY());
	}
}


void Snake:: appearanceSnake(bool random)
{
	int x;
	int y;
	int num = 0;
	
	if (random)
	{
		srand((int)time(NULL));
		x = rand() % 78 + 1;
		y = rand() % 19 + 1;
		reappearance[iReappearance].set(x, y);
		iReappearance++;
	}
	else
	{
		x = reappearance[iReappearance].getX();
		y = reappearance[iReappearance].getY();
		iReappearance++;
	}
	if (direction != 4)
	{
		body[size - 1].set(x, y);
		setTextColor(color);
		theGame->updateBoard(shape, body[size - 1].getX(), body[size - 1].getY());
		body[size - 1].draw(shape);

		for (int i = size - 1; i > 0; i--)
		{
			body[i - 1].set(body[i].next(direction).getX(), body[i].next(direction).getY());
			setTextColor(color);
			theGame->updateBoard(shape, body[i - 1].getX(), body[i - 1].getY());
			body[i - 1].draw(shape);
		}
	}
	else
	{
		body[0].set(x, y);
		setTextColor(color);
		theGame->updateBoard(shape, body[0].getX(), body[0].getY());
		body[0].draw(shape);
	}
	if (theGame->checkIfNumberPoint(body[0].next(direction)))
		theGame->removeNumberFromBoard(body[0].next(direction), num);
}


void Snake::updateSnakeCounter(bool random)
{
	snakeCounter++;
	if (snakeCounter == 5)
	{
		appearanceSnake(random);
		snakeCounter = 0;
	}
}



void Snake::stuckObjects(bool &stopSnake1, bool &stopSnake2)
{
	for (int i = 0; i < size; i++)
	{
		if (theGame->isEatingNumbers(body[i].next(direction)))
		{
			if (shape == '@')
				stopSnake1 = true;
			else
				stopSnake2 = true;
		}
		else if (theGame->isFlyingLines(body[i].next(direction)))
		{
			if (shape == '@')
				stopSnake1 = true;
			else
				stopSnake2 = true;
		}
		else if (theGame->isFlyingRows(body[i].next(direction)))
		{
			if (shape == '@')
				stopSnake1 = true;
			else
				stopSnake2 = true;
		}
		else if (theGame->isBullet(body[i].next(direction)))
		{
			if (shape == '@')
				stopSnake1 = true;
			else
				stopSnake2 = true;
		}
	}
}