#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include <iostream>
#include "io_utils.h"
#include <vector>
#include "Snake.h"
#include "GameManager.h"
#include "Missions.h"
#include "Math.h"
#include "Bullet.h"
#include "Objects.h"
#include "FlyingLines.h"
#include "FlyingRows.h"
#include "EatingNumbers.h"


enum { ROWS = 21, COLS = 80 };

class TheSnakesGame {

	enum { ESC = 27 };
	struct NumbersOnBoard {

		int length;
		Point startPoint;//the left side of the number
		int numOnBoard;
		int counter = 0;
	};
	int logSize=0;
	enum { phSize = 60 };
	struct NumbersOnBoard arrOfNum [phSize];
	Snake **s;
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	char copyBoard[ROWS][COLS + 1];
	void handleObjectCreationFromBoard(int row, int col);
	int score1 = 0, score2 = 0;
	int missingNum;//the missing num of the exercise in mission 7
	Objects *objects[5];
	vector<NumbersOnBoard> replayNum;
	vector <char> keys;
	vector<int> timeKey;
public:
	TheSnakesGame(int size = 2)
	{	
		s = new Snake*[size];
		s[0] = new Snake(Point(10, 9), YELLOW, 3);
		s[1] = new Snake(Point(70, 9), LIGHTMAGENTA, 3);
		

		objects[0] = new FlyingRows(Point(45, 19), true);
		objects[1] = new FlyingRows(Point(55, 15), false);
		objects[2] = new FlyingLines(Point(50, 15), true);
		objects[3] = new FlyingLines(Point(30, 19), false);

		objects[4] = new EatingNumbers(Point(10, 19));
	}
	~TheSnakesGame()
	{
		delete s[0];
		delete s[1];
		delete[]s;
		for (int i = 0; i < 5; i++)
			delete objects[i];
		
	}

	int countDigit(int num);
	void restartBullets();
	void AppearanceNumbers();
	void setBoard(const char* boardToCopy[ROWS]);
	void init(int flag);
	bool isWall(const Point& p) {
		return board[p.getY()][p.getX()] == '+';
	}
	bool isSnake(const Point& p,char shape) {
		return ((board[p.getY()][p.getX()] == shape));
	}
	
	void BoardToCopy(char **boardToCopy);
	bool isNumber(const Point &p);
	void run(int indexMission, Missions &mission, bool &pause0, bool &pause1, bool replay, int &countKey, int &count, int &countNumbers);
	bool checkPoint(int y, int x, int length);
	void printNumbers(int y, int x, int num,int length);
	void removeNumberFromBoard(const Point &p ,int &num);
	int removeFromArr( Point p, int &num);
	void updateBoard(char ch,int x, int y);
	
	bool  isNumberValid(Point p, int indexMission, int num, Missions &mission);
	void removeHalfNumbers();
	int checkRightAnswers(int indexMission, Missions &mission);
	void removeAllArr();
	int SnakeAteNumber(int countNumbers, int *indexMission, int isNum, Missions &mission, bool *isGameOver, int indexSnake, int &countKey);
	void isGameOver(bool _isGameOver, int indexSnake);
	void soundWrong();
	void soundRight();
	void soundWin();
	void soundLose();
	bool checkIfNumberPoint(Point p);
	bool isFlyingRows(Point p);
	bool isFlyingLines(Point p);
	bool isBullet(Point p);
	int bestWay(int indexMission, Missions &mission);
	int startNewMission(int countNumbers, int *indexMission, Missions &mission, int &countKey);
	void removeSnake(char shape, bool *isGameOver1, bool *isGameOver2);
	void appearanceSnake(char shape);
	bool isEatingNumbers(Point p);
	void setOnBoardEatingNumbers(bool onBoard);
	void setOnBoardFlyingsRows(bool onBoard, Point p);
	void replayRun(int indexMission, Missions &mission, bool &pause0, bool &pause1, int &countNumbers, int &countKey);
	void setReplayNum();
	void saveReplay();

	
};


#endif