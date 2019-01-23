#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "Point.h"
#include "Missions.h"
class TheSnakesGame;



class Objects
{

	enum { HITSNAKE1 = 1, HITSNAKE2 = 2, HITNUMBER = 3, HITNOTHING = 0 };
public:
	virtual void move(int indexMission, Missions &mission);
	virtual Point *getPoint() = 0;
	virtual void setDirection(int dir) = 0;
	virtual void setGame(TheSnakesGame* _theGame) = 0;
	virtual Color getColor() = 0;
	virtual char getShape() = 0;
	virtual int getDirection() = 0;
	virtual void checkOnBoard(bool *stopSnake1, bool *stopSnake2, int indexMission, int countNumbers, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey);
	virtual int checkHits(int countNumbers, int *indexMission, Missions mission, bool *isGameOver1, bool *isGameOver2, int &countKey);
	bool isNumber();
	virtual bool getIsDirectionChanged() = 0;
	virtual TheSnakesGame* getTheGame() = 0;
	void removeObject(Point p);
	void appearance(Point p);
	virtual void setOnBoard(bool _onBoard) = 0;
	virtual bool getOnBoard() = 0;
	virtual void setPositionStart(Point p) = 0;
	virtual Point getPositionStart() = 0;
	virtual void setPoint(Point p) = 0;
	virtual void setPointToStart() = 0;
};
#endif // !_OBJECTS_H_
