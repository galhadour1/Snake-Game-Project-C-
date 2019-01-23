#ifndef _FLYINGLINES_H_
#define _FLYINGLINES_H_

#include "Objects.h"

class FlyingLines :public Objects
{
	Point point;
	int direction;
	char shape = '!';
	Color color = LIGHTRED;
	bool isDirectionChanged;
	TheSnakesGame *theGame;
	enum { HITSNAKE = 1, HITOTHERSNAKE = 2, HITNUMBER = 3, HITNOTHING = 0 };
	bool onBoard = true;
	Point positionStart;
public:
	FlyingLines(Point _point, bool _isDirectionChanged) {
		point.set(_point.getX(), _point.getY());
		isDirectionChanged = _isDirectionChanged;
		positionStart.set(_point.getX(), _point.getY());
	}


	virtual void setDirection(int dir) {
		direction = dir;
	}

	virtual Point *getPoint() {
		return &point;
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

	virtual void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;
	}

	virtual TheSnakesGame*getTheGame() {
		return theGame;
	}
	virtual void setOnBoard(bool _onBoard) {
		onBoard = _onBoard;
	}
	virtual bool getOnBoard() {
		return onBoard;
	}
	virtual void setPositionStart(Point p) { positionStart.set(p.getX(), p.getY()); }
	virtual Point getPositionStart() { return positionStart; }
	virtual void setPoint(Point p) { point.set(p.getX(), p.getY()); }
	virtual void setPointToStart() { 
		if (isDirectionChanged)
			point.set(50, 15);
		else
			point.set(30, 19);
	}
};
#endif // !_FLYINGLINES_H_
