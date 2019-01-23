#ifndef _EATINGNUMBERS_H_
#define _EATINGNUMBERS_H_

#include "Objects.h"


using namespace std;
class EatingNumbers : public Objects
{
	Point point;
	int direction;
	char shape = '%';

	Color color = LIGHTBLUE;
	bool isDirectionChanged = false;

	TheSnakesGame* theGame;
	bool onBoard = true;
	enum { HITSNAKE1 = 1, HITSNAKE2 = 2, HITNUMBER = 3, HITNOTHING = 0 };
	Point positionStart;
public:
	EatingNumbers(Point _point) {
		point.set(_point.getX(), _point.getY());
		positionStart.set(_point.getX(), _point.getY());
	}


	virtual void setDirection(int dir) {
		direction = dir;
	}


	virtual bool getIsDirectionChanged()
	{
		return isDirectionChanged;
	}

	virtual Point *getPoint()
	{
		return &point;
	}

	virtual Color getColor()
	{
		return color;
	}

	virtual char getShape()
	{
		return shape;
	}

	virtual int getDirection()
	{
		return direction;
	}

	virtual TheSnakesGame*  getTheGame(){return theGame;}

	virtual void setGame(TheSnakesGame* _theGame){theGame = _theGame;}

	virtual void move(int indexMission, Missions &mission);
	virtual void setOnBoard(bool _onBoard) {
		onBoard = _onBoard;
	}
	virtual bool getOnBoard() {
		return onBoard;
	}
	virtual void checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission,int countNumbers, Missions &mission, bool *isGameOver1, bool *isGameOver2, int &countKey);
	virtual int checkHits(int countNumbers, int *indexMission, Missions &mission, bool *isGameOver1, bool *isGameOver2, int &countKey);
	virtual void setPositionStart(Point p) { positionStart.set(p.getX(), p.getY()); }
	virtual Point getPositionStart() { return positionStart; }
	virtual void setPoint(Point p) { point.set(p.getX(), p.getY()); }
	virtual void setPointToStart() { point.set(10, 19); }
};
#endif // ! _EATINGNUMBERS_H_
