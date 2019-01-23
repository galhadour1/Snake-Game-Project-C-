#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "Bullet.h"

#include "Objects.h"

class TheSnakesGame;

class Snake
{

	int size;
	char arrowKeys[4];
	Color color = BLUE;
	enum { MAXSIZE = 14 };
	int direction;
	Point *body;
	char shape;
	bool isDirectionChanged = false;
	Point *positionStart;


	enum { MAXBULLETS = 5 };
	Bullet *bullet;
	int numBullets = 5;
	int emptyPlace = 0;
	TheSnakesGame* theGame;
	enum { HITSNAKE = 1, HITOTHERSNAKE = 2, HITNUMBER = 3, HITNOTHING = 0, HITFLYINGROWS = 5};
	int snakeCounter = 0;
	int replaySnakeCounter = 0;
	int replayDirection;
	Point reappearance[15];//save the random point of the appearance of the snake
	int iReappearance = 0;

public:
	
	Snake(Point Start, Color _color, int length)
	{
		color = _color;
		size = length;
		body = new Point[MAXSIZE];
		positionStart = new Point[MAXSIZE];

		for (int i = 0; i < size; i++)
		{

			body[i].set(Start.getX(), Start.getY());
		}
		bullet = new Bullet[MAXBULLETS];
	
	}
	
	int isNumberSnake(int indexMission, bool *isGameOver, Missions &mission);
	bool  biggerSnake();
	~Snake()
	{
		delete[]positionStart;
		delete[]body;
		delete[]bullet;
	}


	void setShape(char ch);

	void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;
		for (int i = 0; i < MAXBULLETS; i++)
			bullet[i].setGame(_theGame);
	}
	void setPosition(int y, int x);
	
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}
	void setColor(Color c) {
		color = c;
	}
	void setSize(int _size) {
		size = _size;
	}
	void move();
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}

	void setBulletDirection(){
		if (direction == 4)
		{
			bullet[emptyPlace].setDirection(rand()%4);
		}
		else
			bullet[emptyPlace].setDirection(direction);
	}


	void setNumBullet(int num) {
		numBullets = num;
	}

	int getNumBullets() {
		return numBullets;
	}
	
	void setBulletPoint() {
		bullet[emptyPlace].setPoint(body[0].next(direction));
	}

	void setBulletOnBoard(bool _onBoard) {
		bullet[emptyPlace].setOnBoard(_onBoard);
	}

	void findEmptyPlace();

	void clearBullets();

	void checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission, int countNumbers, Missions mission ,bool *isGameOver1, bool *isGameOver2, int &countKey);

	void removeSnake();

	void appearanceSnake(bool random);


	void updateSnakeCounter(bool random);

	int getSnakeCounter() {
		return snakeCounter;
	}

	void resetSnakeCounter() {
		snakeCounter = 0;
	}
	void setPositionStart(Point *p) {
		for (int i = 0; i < size; i++)
			positionStart[i].set(p[i].getX(), p[i].getY());
	}
	Point *getPositionStart() { return positionStart; }
	Point *getBody() { return body; }
	void setReplaySnakeCounter(int counter) { replaySnakeCounter = counter; }
	int getReplaySnakeCounter() { return replaySnakeCounter; }
	void setReplayDirection() { replayDirection = direction; }
	int getReplayDirection() { return replayDirection; }
	void setSnakeCounter(int counter) { snakeCounter = counter; }
	void stuckObjects(bool &stopSnake1, bool &stopSnake2);
	void setIReappearance() { iReappearance = 0; }
};


#endif