#ifndef _BULLET_H_
#define _BULLET_H_



#include "Objects.h"

class TheSnakesGame;


class Bullet:public Objects
{
	Point bullet;
	int direction;
	char shape = '*';
	char arrowKey;
	Color color = BLUE;
	TheSnakesGame* theGame;
	char snakeShape;
	bool onBoard = false;
	bool isDirectionChanged = false;
	enum { HITSNAKE = 1, HITOTHERSNAKE = 2, HITNUMBER = 3, HITNOTHING = 0, HITFLYINGLINES = 4, HITFLYINGROWS = 5 };
	Point positionStart;
public:
	Bullet() {
		
	}

	void setArrowKey(char _arrowKey) {
		arrowKey = _arrowKey;
	}

	void setSnakeShape(char ch){
		snakeShape = ch;
	}

	void setColor(Color c) {
		color = c;
	}

	virtual void setDirection(int dir) {
		direction = dir;
	}

	virtual void move(int indexMission, Missions &mission);
	bool isNumberBullet();
	virtual void setOnBoard(bool _onBoard){
		onBoard = _onBoard;
	}

	int getX() {
		return bullet.getX();
	}
	int getY() {
		return bullet.getY();
	}


	virtual bool getOnBoard() {
		return onBoard;
	}
	int checkHits(int countNumbers, int *indexMission, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey);



	virtual Point *getPoint() {
		return &bullet;
	}

	virtual Color getColor() {
		return color;
	}

	virtual char getShape() {
		return shape;
	}

	virtual int getDirection() {
		return direction;
	}


	virtual bool getIsDirectionChanged() {
		return isDirectionChanged;
	}
	virtual void setGame(TheSnakesGame* _theGame) {theGame = _theGame;}

	virtual TheSnakesGame*getTheGame() {return theGame;}
	virtual void setPositionStart(Point p) { positionStart.set(p.getX(), p.getY()); }
	virtual Point getPositionStart() { return positionStart; }
	virtual void setPoint(Point p) { bullet.set(p.getX(), p.getY()); }
	virtual void setPointToStart() {
		bullet.set(1, 1);
	}
};



#endif // !_BULLET_H
