#include "TheSnakesGame.h"
#include <time.h>



void TheSnakesGame::handleObjectCreationFromBoard(int row, int col)
{
	char ch = board[row][col];
	if (ch == '@')
		if ((board[row][col]!='+')&&(board[row][col]!='#'))
			s[0]->setPosition(row, col);
	if (ch == '#')
		if((board[row][col] != '+') && (board[row][col] != '@'))
			s[1]->setPosition(row, col);
}
void TheSnakesGame::setBoard(const char* boardToCopy[ROWS])
{
	setTextColor(WHITE);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}



void TheSnakesGame::BoardToCopy(char **boardToCopy)
{
	setTextColor(WHITE);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{

			copyBoard[i][j] = boardToCopy[i][j];
		}
		copyBoard[i][COLS] = '\0';
	}
}


void TheSnakesGame::init(int flag)
{

	if ((flag == 6) || (flag == 4) || (flag == 5))//options 4,5,6 in the secondary menu
	{
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				gotoxy(j, i + 3);
				cout << originalBoard[i][j];
				cout.flush();
				board[i][j] = originalBoard[i][j];
				handleObjectCreationFromBoard(i, j);
				
				

			}

		}
	}
	else if (flag == 3)//option 3 in the secondary menu
	{
		for (int i = 0; i < ROWS+3; i++) {
			for (int j = 0; j < COLS; j++) {
				gotoxy(j, i + 3);
				if ((board[i][j] == '#') || (board[i][j] == '@'))
					cout << ' ';
				else
					cout << board[i][j];
				cout.flush();
				
				
			}

		}

	}
	else if (flag == 7)//option 7 in the secondary menu
	{
		setTextColor(WHITE);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {

				if (originalBoard[i][j] == '@' || originalBoard[i][j] == '#')
					board[i][j] = ' ';
				else
					board[i][j] = originalBoard[i][j];
				gotoxy(j, i + 3);
				cout << board[i][j];
				cout.flush();

			}

		}
		for (int i = 0; i < (int)replayNum.size(); i++)
			if (replayNum[i].counter == 0)
				printNumbers(replayNum[i].startPoint.getX(), replayNum[i].startPoint.getY(), replayNum[i].numOnBoard, replayNum[i].length);
	}
	if (flag == 6)//option 6 in the secondary menu-start new game
	{
		s[0]->setSize(3);
		s[1]->setSize(3);
		s[0]->setDirection(3);
		s[1]->setDirection(2);
		s[0]->setReplayDirection();
		s[1]->setReplayDirection();
		s[0]->setPositionStart(s[0]->getBody());
		s[1]->setPositionStart(s[1]->getBody());
		s[0]->resetSnakeCounter();
		s[1]->resetSnakeCounter();
		score1 = 0;
		score2 = 0;
		for (int i = 0; i < 5; i++)
		{
			objects[i]->setDirection(i);
			objects[i]->setPointToStart();
			objects[i]->setPositionStart(*objects[i]->getPoint());
		}
		
			
	}
	else if ((flag == 5) || (flag == 4))
	{
		s[0]->setDirection(3);
		s[1]->setDirection(2);
		s[0]->resetSnakeCounter();
		s[1]->resetSnakeCounter();
		for (int i = 0; i < 5; i++)
		{
			objects[i]->setDirection(i);
			if (flag == 4)
				objects[i]->setPoint(objects[i]->getPositionStart());
		}
	}
	else if (flag == 7)
	{
		//s[0]->appearanceSnake(false);
		//s[1]->appearanceSnake(false);
		s[0]->setPosition(s[0]->getPositionStart()->getY(), s[0]->getPositionStart()->getX());
		s[1]->setPosition(s[1]->getPositionStart()->getY(), s[1]->getPositionStart()->getX());
		s[0]->setDirection(s[0]->getReplayDirection());
		s[1]->setDirection(s[1]->getReplayDirection());
		s[0]->setSnakeCounter(s[0]->getReplaySnakeCounter());
		s[1]->setSnakeCounter(s[1]->getReplaySnakeCounter());
		for (int i = 0; i < 5; i++)
		{
			objects[i]->setDirection(i);
			objects[i]->setPoint(objects[i]->getPositionStart());
		}
		
	}
	s[0]->setShape('@');
	s[1]->setShape('#');
	
	s[0]->setArrowKeys("wxad");
	s[1]->setArrowKeys("imjl");
	s[0]->setGame(this);
	s[1]->setGame(this);

	for (int i = 0; i < 5; i++)
		objects[i]->setGame(this);
}

void TheSnakesGame::restartBullets()
{
	s[0]->clearBullets();
	s[1]->clearBullets();
	s[0]->setNumBullet(5);
	s[1]->setNumBullet(5);
}

void TheSnakesGame::run(int indexMission, Missions &mission, bool &pause0, bool &pause1, bool replay, int &countKey, int &count, int &countNumbers)
{
	PlaySound(NULL, NULL, 0);
	PlaySound(L"go-go-go.wav", NULL, SND_FILENAME | SND_ASYNC);
	
	char key = 0;
	GameManager stop;

	int isNum1, isNum2;
	bool isGameOver1 = false, isGameOver2 = false;
	int dir;
	bool stopSnake1, stopSnake2;

	srand((int)time(NULL));
	gotoxy(2, 1);
	setTextColor(LIGHTMAGENTA);
	cout << "Bullets: " << s[1]->getNumBullets();

	gotoxy(69, 1);
	setTextColor(YELLOW);
	cout << "Bullets: " << s[0]->getNumBullets();

	gotoxy(2, 2);
	setTextColor(LIGHTMAGENTA);
	cout << "Snake 2: " << score2;

	gotoxy(69, 2);
	setTextColor(YELLOW);
	cout << "Snake 1: " << score1;
	if (replay)
		replayRun(indexMission, mission, pause0, pause1, countNumbers, countKey);
	else
	{
		do
		{
			if (_kbhit())
			{
				key = _getch();
				keys.push_back(key);
				timeKey.push_back(countKey);

				if ((dir = s[0]->getDirection(key)) != -1)
					s[0]->setDirection(dir);
				else if ((dir = s[1]->getDirection(key)) != -1)
					s[1]->setDirection(dir);
				else if (key == 'z')
				{
					if (s[0]->getNumBullets() != 0)
					{
						s[0]->setBulletDirection();
						s[0]->setNumBullet((s[0]->getNumBullets()) - 1);
						s[0]->setBulletPoint();
						s[0]->setBulletOnBoard(true);
						s[0]->findEmptyPlace();
						PlaySound(L"Ci1egglay.wav", NULL, SND_FILENAME | SND_ASYNC);
					}
				}
				else if (key == 'n')
				{
					if (s[1]->getNumBullets() != 0)
					{

						s[1]->setBulletDirection();
						s[1]->setNumBullet((s[1]->getNumBullets()) - 1);
						s[1]->setBulletPoint();
						s[1]->setBulletOnBoard(true);
						s[1]->findEmptyPlace();
						PlaySound(L"Ci1egglay.wav", NULL, SND_FILENAME | SND_ASYNC);
					}
				}
			}

			if ((countNumbers != 60) && (count == 5))
			{
				AppearanceNumbers();
				count = 0;
				countNumbers++;

				if (((s[0]->getSnakeCounter() > 0) && (s[0]->getSnakeCounter() < 5)) || ((s[0]->getSnakeCounter() == 0) && (pause0)))
					s[0]->updateSnakeCounter(true);
				if (((s[1]->getSnakeCounter() > 0) && (s[1]->getSnakeCounter() < 5)) || ((s[1]->getSnakeCounter() == 0) && (pause1)))
					s[1]->updateSnakeCounter(true);
			}
			else if (countNumbers == 60)
			{
				indexMission = checkRightAnswers(indexMission, mission);
				countNumbers = startNewMission(countNumbers, &indexMission, mission, countKey);

			}
			count++;

			isNum1 = s[0]->isNumberSnake(indexMission, &isGameOver1, mission);
			if (isNum1 != 2)//the snake ate a number
				countNumbers = SnakeAteNumber(countNumbers, &indexMission, isNum1, mission, &isGameOver2, 0, countKey);

			isNum2 = s[1]->isNumberSnake(indexMission, &isGameOver2, mission);
			if (isNum2 != 2)//the snake ate a number
				countNumbers = SnakeAteNumber(countNumbers, &indexMission, isNum2, mission, &isGameOver1, 1, countKey);


			if ((isGameOver1) || (isGameOver2))
				key = ESC;
			setTextColor(WHITE);

			stopSnake1 = false;
			stopSnake2 = false;

			for (int j = 0; j < 2; j++)
				objects[j]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey);
			if (stopSnake1 == true)
				pause0 = true;
			else if (stopSnake2 == true)
				pause1 = true;

			for (int i = 0; i < 2; i++)
			{
				s[0]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey);
				s[1]->checkOnBoard(&stopSnake2, &stopSnake1, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey);
				for (int j = 2; j < 5; j++)
					objects[j]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey);
				if (stopSnake1 == true)
					pause0 = true;
				else if (stopSnake2 == true)
					pause1 = true;
			}

			if ((isGameOver1) || (isGameOver2))
				key = ESC;


			s[0]->stuckObjects(stopSnake1, stopSnake2);
			s[1]->stuckObjects(stopSnake1, stopSnake2);
			if (stopSnake1 == true)
				pause0 = true;
			else if (stopSnake2 == true)
				pause1 = true;

			if ((s[0]->getSnakeCounter() > 0) && (s[0]->getSnakeCounter() < 5))
				pause0 = true;
			if ((s[1]->getSnakeCounter() > 0) && (s[1]->getSnakeCounter() < 5))
				pause1 = true;

			if ((pause0 == true) && (pause1 == true))//snake-s[1]  stop and s[0] stop 
			{
				if (s[0]->getSnakeCounter() == 0)
					s[0]->removeSnake();
				else
					pause0 = false;
				if (s[1]->getSnakeCounter() == 0)
					s[1]->removeSnake();
				else
					pause1 = false;
			}
			else if ((pause1 == true) && (pause0 == false))//snake-s[1]  stop and s[0] move 
			{
				if (s[1]->getSnakeCounter() == 0)
					s[1]->removeSnake();
				else
					pause1 = false;

				s[0]->move();
			}
			else if ((pause0 == true) && (pause1 == false))//snake-s[0]  stop and s[1] move 
			{
				if (s[0]->getSnakeCounter() == 0)
					s[0]->removeSnake();
				else
					pause0 = false;

				s[1]->move();
			}
			else
			{
				pause0 = false;
				s[0]->move();
				pause1 = false;
				s[1]->move();
			}

			countKey++;

			Sleep(150);

			gotoxy(2, 1);
			setTextColor(LIGHTMAGENTA);
			cout << "Bullets: " << s[1]->getNumBullets();

			gotoxy(69, 1);
			setTextColor(YELLOW);
			cout << "Bullets: " << s[0]->getNumBullets();

		} while (key != ESC);
	}
	
	system("cls");
	
	if ((isGameOver1) || (isGameOver2))
	{
		key = ' ';
		system("cls");
		isGameOver(isGameOver1, 0);
		isGameOver(isGameOver2, 1);

		do {

			if (_kbhit())
			{

				key = _getch();
			
			}
			
		} while (key != ESC);
		if (key == ESC)
		{
			system("cls");
			stop.mainMenu();
		}
	}
	else
		stop.SecondaryMenu(this, indexMission  , mission, pause0, pause1, countKey, count, countNumbers);
	
}

void TheSnakesGame::removeAllArr()
{
	for (int i = 0; i < logSize; i++)
	{
		arrOfNum[i].length = 0;
		arrOfNum[i].numOnBoard = -1;
		arrOfNum[i].startPoint.set(1,1);
	}
	logSize = 0;
}
void TheSnakesGame:: removeHalfNumbers()
{
	int randNum;
	int half;
	half = (logSize) / 2;
	while ((half != 0)&&(logSize!=0))
	{
		randNum = rand() % logSize;
		removeNumberFromBoard(arrOfNum[randNum].startPoint, arrOfNum[randNum].numOnBoard);
		
		half--;
		
	}

}

int TheSnakesGame::checkRightAnswers(int indexMission,Missions &mission)
{
	int x, y;
	int i;
	int countGoodAnswers = 0;
	for ( i = 0; i < logSize; i++)
	{
		if (isNumberValid(arrOfNum[i].startPoint,indexMission,arrOfNum[i].numOnBoard, mission) == true)
		{
			x = arrOfNum[i].startPoint.getX();
			y = arrOfNum[i].startPoint.getY();
			gotoxy(x, y + 3);
			setTextColor(LIGHTRED);
			cout << arrOfNum[i].numOnBoard;
			Sleep(700);
			gotoxy(x, y + 3);
			setTextColor(WHITE);
			cout << arrOfNum[i].numOnBoard;
			countGoodAnswers++;
		}
	}
	if (countGoodAnswers == 0)
	{
		gotoxy(2, 0);
		for (int i = 0; i<79; i++)
			cout << " ";
		gotoxy(2, 0);
		setTextColor(LIGHTRED);
		cout << " THERE IS NOT RIGHT ANSWER ON THE BOARD!! SORRY :(\n";
		Sleep(1000);
	
	
		
	}
	return indexMission;
}

void TheSnakesGame::removeNumberFromBoard(const Point &p, int &num)
{
	int lengthNum;
	int x = p.getX();
	int y = p.getY();
	Point p1;

	while ((board[p.getY()][x] != ' ') && (board[p.getY()][x] != '+') && (board[p.getY()][x] != '#') && (board[p.getY()][x] != '@') && (board[p.getY()][x] != '*') && (board[p.getY()][x] != '!') && (board[p.getY()][x] != '$') && (board[p.getY()][x] != '%'))
	{
		x--;	
	}
	x++;
	p1.set(x, y);

	lengthNum = removeFromArr(p1, num);
	for (int i = 0; i < lengthNum; i++)
	{
		board[y][x + i] = ' ';
		gotoxy(p1.getX() + i, p1.getY() + 3);
		cout << " ";

	}


}




int TheSnakesGame::removeFromArr(Point p, int &num)
{
	int i = 0;
	int length;
	
	while (!((arrOfNum[i].startPoint.getX() == p.getX()) && (arrOfNum[i].startPoint.getY() == p.getY())))
	{
		i++;
	}
	num = arrOfNum[i].numOnBoard;
	length = arrOfNum[i].length;
	logSize--;
	arrOfNum[i] = arrOfNum[logSize];

	return length;
}





bool TheSnakesGame::checkPoint(int y, int x, int length)
{


	for (int i = 0; i < length; i++)
	{

		if (board[y][x + i] != ' ')
		{
			return false;
		}

		if (board[y + 1][x + i] != ' ')
		{
			return false;
		}


		if (board[y - 1][x + i] != ' ')
		{
			return false;
		}

	}

	if (x > 0)
	{
		if (board[y][x - 1] != ' ')
		{
			return false;
		}

	}

	if (board[y][x + length] != ' ')
	{
		return false;
	}

	return true;
}



void TheSnakesGame::AppearanceNumbers()
{

	int x, y;
	int num;
	int probability;
	srand((int)time(NULL));
	
	setTextColor(WHITE);
	probability = rand() % 3;
	if (probability == 0)
		num = rand() % 26;
	else if (probability == 1)
		num = rand() % 55 + 26;
	else
		num = rand() % 87 + 82;
	arrOfNum[logSize].length = countDigit(num);
	arrOfNum[logSize].numOnBoard = num;
	
	do
	{
		x = rand() % 79;
		y = rand() % 20;
	} while (!(checkPoint(y, x, arrOfNum[logSize].length)));

	arrOfNum[logSize].startPoint.set(x,y);
	replayNum.push_back(arrOfNum[logSize]);
	replayNum[replayNum.size() - 1].counter++;
	printNumbers(x, y, num, arrOfNum[logSize].length);

	logSize++;

}

int TheSnakesGame::countDigit(int num)
{
	int count = 1;
	if (num < 0)
	{
		count++;
		num = num*(-1);
	}
	while (num >= 10)
	{
		count++;
		num = num / 10;
	}
	return count;
}

void TheSnakesGame:: printNumbers(int y,int x, int num,int length)
{
	if (length == 1)
		board[x][y] = num + '0';
	if (length == 2)
	{
		board[x][y] = (num / 10)+'0';
		board[x][y+1] = (num % 10) + '0';
	}
	if (length == 3)
	{
		board[x][y] = (num / 100) + '0';
		board[x][y+1] = ((num /10) % 10) + '0';
		board[x][y+2] = (num % 10) + '0';
	}

	setTextColor(WHITE);
	gotoxy(y, x + 3);
	cout <<num;

}
bool TheSnakesGame:: isNumber(const Point &p)
{
	
	if ((board[p.getY()][p.getX()] >= '0') && (board[p.getY()][p.getX()] <= '9'))
		return true;
	else
		return false;
}

void TheSnakesGame::updateBoard(char ch, int x, int y)
{
	int num;
	if (checkIfNumberPoint(Point(x, y)))
	{
		removeNumberFromBoard(Point(x, y), num);
	}
	board[y][x] = ch;
}


bool TheSnakesGame::isNumberValid(Point p, int indexMission, int num, Missions &mission) 
{
	return mission.isRightAnswer(num, indexMission);
}

int TheSnakesGame::SnakeAteNumber(int countNumbers, int *indexMission, int isNum, Missions &mission , bool *isGameOver, int indexSnake, int &countKey)
{
	if (isNum == 0)//the snake ate the wrong number
	{
		soundWrong();
		if (indexSnake == 0)
		{
			gotoxy(2, 2);
			setTextColor(LIGHTMAGENTA);
			score2++;
			cout << "Snake 2: " << score2;
		}
		else
		{
			gotoxy(69, 2);
			setTextColor(YELLOW);
			score1++;
			cout << "Snake 1: " << score1;
		}
		*indexMission = checkRightAnswers(*indexMission, mission);
		*isGameOver = s[1 - indexSnake]->biggerSnake();
		gotoxy(0, 1);
		setTextColor(LIGHTGREEN);
		cout << "\t\t\t\tSNAKE " << 1 + indexSnake << " YOU CAN DO BETTER!!\n";
		Sleep(1000);
		gotoxy(0, 1);
		for (int i = 0; i < 79; i++)
		{
			cout << " ";
		}

	}
	else//the snake ate the right number 
	{
		soundRight();
		if (indexSnake == 1)
		{
			gotoxy(2, 2);
			setTextColor(LIGHTMAGENTA);
			score2++;
			cout << "Snake 2: " << score2;
		}
		else
		{
			gotoxy(69, 2);
			setTextColor(YELLOW);
			score1++;
			cout << "Snake 1: " << score1;
		}

		gotoxy(0, 1);
		setTextColor(LIGHTGREEN);
		cout << "\t\t\t\tSNAKE " << 1 + indexSnake << " YOU GOT IT!!\n";
		Sleep(1000);
		gotoxy(0, 1);
		for (int i = 0; i < 79; i++)
		{
			cout << " ";
		}
	}
	return startNewMission(countNumbers, indexMission, mission, countKey);
}


void TheSnakesGame::isGameOver(bool _isGameOver,int indexSnake)
{

	if (_isGameOver)
	{
		gotoxy(1, 2);
		if (indexSnake == 0)
			setTextColor(YELLOW);
		else
			setTextColor(LIGHTMAGENTA);
		cout << " \t\t\t\t\t\t\t\t\t\n\tSNAKE NUMBER " << 1 + indexSnake << " WIN!!!\n";
		soundWin();
		Sleep(3000);
		system("cls");
		gotoxy(1, 2);
		if (indexSnake == 0)
			setTextColor(LIGHTMAGENTA);
		else
			setTextColor(YELLOW);

		cout << "\t\t\t\t\t\t\t\t\t\n\tSNAKE NUMBER " << 2 - indexSnake << " YOU LOSE!!!\n";
		soundLose();
		Sleep(3000);
		system("cls");
		setTextColor(LIGHTCYAN);
		PlaySound(L"thats-it.wav", NULL, SND_FILENAME | SND_ASYNC);
		gotoxy(0, 0);
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 78; j++)
				cout << "/";
			cout << endl;
		}
		gotoxy(18, 10);
		cout << "--------------------------------------------------";
		gotoxy(18, 11);
		cout << "-----|||            GAME OVER           ....:) |||";
		gotoxy(0, 0);
		cout << "Press ESC to Main menu";
		gotoxy(18, 12);
		cout << "--------------------------------------------------";
		gotoxy(18, 13);
		Sleep(1000);
	}
}

void TheSnakesGame::soundWrong()
{
	int	randSound = rand() % 5;
	if (randSound == 0)
		PlaySound(L"focus.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 1)
		PlaySound(L"come-on-1.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 2)
		PlaySound(L"no-4.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 3)
		PlaySound(L"ooooh.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 4)
		PlaySound(L"goddamnit.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void TheSnakesGame::soundRight()
{
	int randSound = rand() % 5;
	if (randSound == 0)
		PlaySound(L"yes-hahahaa.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 1)
		PlaySound(L"nice-work.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 2)
		PlaySound(L"yes-2.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 3)
		PlaySound(L"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(L"you-got-it-1.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void TheSnakesGame::soundWin()
{
	int randSound = rand() % 4;
	if (randSound == 0)
		PlaySound(L"happy.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 1)
		PlaySound(L"youre-my-man.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 2)
		PlaySound(L"haha.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 3)
		PlaySound(L"loser2.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 4)
		PlaySound(L"bartlaf3.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void TheSnakesGame::soundLose()
{
	int randSound = rand() % 7;

	if (randSound == 0)
		PlaySound(L"maybe-next-time.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 1)
		PlaySound(L"oh-thats-okay.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 2)
		PlaySound(L"am-i-totally-screwed-or.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 3)
		PlaySound(L"Debbie-Downer-Sad-Trombone.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 4)
		PlaySound(L"im-not-mad.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 5)
		PlaySound(L"crap.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (randSound == 6)
		PlaySound(L"Ci1gameover.wav", NULL, SND_FILENAME | SND_ASYNC);
}



bool TheSnakesGame::checkIfNumberPoint(Point p)
{
	if ((board[p.getY()][p.getX()] >= '0') && (board[p.getY()][p.getX()] <= '9'))
		return true;
	return false;
}


bool TheSnakesGame::isFlyingLines(Point p)
{
	if (board[p.getY()][p.getX()] == '!')
		return true;
	else
		return false;
}

bool TheSnakesGame::isFlyingRows(Point p)
{
	if (board[p.getY()][p.getX()] == '$')
		return true;
	else
		return false;
}

bool TheSnakesGame::isEatingNumbers(Point p)
{
	if (board[p.getY()][p.getX()] == '%')
		return true;
	else
		return false;
}



bool TheSnakesGame::isBullet(Point p)
{
	if (board[p.getY()][p.getX()] == '*')
		return true;
	else
		return false;
}

int TheSnakesGame::bestWay(int indexMission, Missions &mission)
{
	int min = 200;
	int dirX = 4, dirY = 4;
	int wayY = 0, wayX = 0, way = 0;

	int direction = 4;
	for (int i = 0; i < logSize; i++)
	{
		if (isNumberValid(arrOfNum[i].startPoint, indexMission, arrOfNum[i].numOnBoard, mission))
		{
			dirY = objects[4]->getPoint()->getY() - arrOfNum[i].startPoint.getY();
			dirX = objects[4]->getPoint()->getX() - arrOfNum[i].startPoint.getX();
			wayY = abs(objects[4]->getPoint()->getY() - arrOfNum[i].startPoint.getY());
			wayX = abs(arrOfNum[i].startPoint.getX() - objects[4]->getPoint()->getX());


			if (wayX > 40)
			{
				if (dirX > 0)
				{

					dirX = 3;
				}
				else {
					dirX = 2;
				}

				wayX = 79 - wayX;
			}
			else
			{

				if (dirX > 0)
				{

					dirX = 2;
				}
				else {
					dirX = 3;
				}
			}

			if (wayY > 10)
			{
				if (dirY > 0)
				{

					dirY = 1;
				}
				else {
					dirY = 0;
				}

				wayY = 19 - wayY;
			}
			else
			{

				if (dirY > 0)
				{

					dirY = 0;
				}
				else {
					dirY = 1;
				}
			}

			way = wayY + wayX;
			if (way < min)
			{
				if (wayY == 0)
					direction = dirX;
				else
					direction = dirY;

				min = way;
			}
		}
	}
	return direction;
}
int TheSnakesGame:: startNewMission(int countNumbers, int *indexMission, Missions &mission, int &countKey)
{
	removeHalfNumbers();
	countNumbers = countNumbers / 2;
	*indexMission = mission.printMission(*indexMission);
	s[0]->setNumBullet(5);
	s[1]->setNumBullet(5);
	s[0]->clearBullets();
	s[1]->clearBullets();
	saveReplay();
	countKey = 0;
	
	return countNumbers;
}

void TheSnakesGame:: removeSnake(char shape, bool *isGameOver1, bool *isGameOver2)
{
	if (shape == '@')
	{
		s[0]->removeSnake();
		gotoxy(2, 2);
		setTextColor(LIGHTMAGENTA);
		score2++;
		cout << "Snake 2: " << score2;
		gotoxy(0, 1);
		setTextColor(LIGHTGREEN);
		cout << "\t\t\t\tSNAKE 1 BE CAREFUL!!\n";
		Sleep(1000);
		gotoxy(0, 1);
		for (int i = 0; i < 79; i++)
		{
			cout << " ";
		}
		*isGameOver2 = s[1]->biggerSnake();
	}
	else
	{
		s[1]->removeSnake();
		gotoxy(69, 2);
		setTextColor(YELLOW);
		score1++;
		cout << "Snake 1: " << score1;
		gotoxy(0, 1);
		setTextColor(LIGHTGREEN);
		cout << "\t\t\t\tSNAKE 2 BE CAREFUL!!\n";
		Sleep(1000);
		gotoxy(0, 1);
		for (int i = 0; i < 79; i++)
		{
			cout << " ";
		}
		*isGameOver1 = s[0]->biggerSnake();
	}
}

void TheSnakesGame::appearanceSnake(char shape)
{
	if (shape == '@')
		s[0]->appearanceSnake(true);
	else
		s[1]->appearanceSnake(true);
}


void TheSnakesGame::setOnBoardEatingNumbers(bool onBoard)
{
	objects[4]->setOnBoard(onBoard);
}


void TheSnakesGame::setOnBoardFlyingsRows(bool onBoard, Point p)
{
	if (objects[0]->getPoint()->getX() == p.getX())
	{
		if (objects[0]->getPoint()->getY() == p.getY())
			objects[0]->setOnBoard(onBoard);
	}
	else if (objects[1]->getPoint()->getX() == p.getX())
	{
		if (objects[1]->getPoint()->getY() == p.getY())
			objects[1]->setOnBoard(onBoard);
	}
}



void TheSnakesGame::replayRun(int indexMission, Missions &mission, bool &pause0, bool &pause1, int &countNumbers, int &countKey)
{
	PlaySound(NULL, NULL, 0);
	PlaySound(L"go-go-go.wav", NULL, SND_FILENAME | SND_ASYNC);

	char key = 0;
	GameManager stop;

	int count = 0;
	bool isGameOver1 = false, isGameOver2 = false;
	int dir;
	int countKey1 = 0, indexKey = 0, indexNum = 0;
	bool stopSnake1, stopSnake2;
	bool found = false;

	gotoxy(2, 1);
	setTextColor(LIGHTMAGENTA);
	cout << "Bullets: " << s[1]->getNumBullets();

	gotoxy(69, 1);
	setTextColor(YELLOW);
	cout << "Bullets: " << s[0]->getNumBullets();

	gotoxy(2, 2);
	setTextColor(LIGHTMAGENTA);
	cout << "Snake 2: " << score2;

	gotoxy(69, 2);
	setTextColor(YELLOW);
	cout << "Snake 1: " << score1;

	s[0]->setIReappearance();
	s[1]->setIReappearance();
	
	for (int i = 0; i < (int)replayNum.size() && !found; i++)
	{
		if (replayNum[i].counter == 1)
		{
			indexNum = i;
			found = true;
			countNumbers = i;
			logSize = i;
		}
		else
			arrOfNum[i] = replayNum[i];
	}
	do
	{
		if (countKey1 == timeKey[indexKey])
		{
			key = keys[indexKey];
			indexKey++;

			if ((dir = s[0]->getDirection(key)) != -1)
				s[0]->setDirection(dir);
			else if ((dir = s[1]->getDirection(key)) != -1)
				s[1]->setDirection(dir);
			else if (key == 'z')
			{
				if (s[0]->getNumBullets() != 0)
				{
					s[0]->setBulletDirection();
					s[0]->setNumBullet((s[0]->getNumBullets()) - 1);
					s[0]->setBulletPoint();
					s[0]->setBulletOnBoard(true);
					s[0]->findEmptyPlace();
					PlaySound(L"Ci1egglay.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
			}
			else if (key == 'n')
			{
				if (s[1]->getNumBullets() != 0)
				{

					s[1]->setBulletDirection();
					s[1]->setNumBullet((s[1]->getNumBullets()) - 1);
					s[1]->setBulletPoint();
					s[1]->setBulletOnBoard(true);
					s[1]->findEmptyPlace();
					PlaySound(L"Ci1egglay.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
			}
		}

		if ((countNumbers != 60) && (count == 5))
		{
			printNumbers(replayNum[indexNum].startPoint.getX(), replayNum[indexNum].startPoint.getY(), replayNum[indexNum].numOnBoard, replayNum[indexNum].length);
			arrOfNum[logSize] = replayNum[indexNum];
			indexNum++;
			logSize++;
			count = 0;
			countNumbers++;

			if (((s[0]->getSnakeCounter() > 0) && (s[0]->getSnakeCounter() < 5)) || ((s[0]->getSnakeCounter() == 0) && (pause0)))
				s[0]->updateSnakeCounter(false);
			if (((s[1]->getSnakeCounter() > 0) && (s[1]->getSnakeCounter() < 5)) || ((s[1]->getSnakeCounter() == 0) && (pause1)))
				s[1]->updateSnakeCounter(false);
		}

		count++;

		setTextColor(WHITE);

		stopSnake1 = false;
		stopSnake2 = false;

		for (int j = 0; j < 2; j++)
			objects[j]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey1);
		if (stopSnake1 == true)
			pause0 = true;
		else if (stopSnake2 == true)
			pause1 = true;

		for (int i = 0; i < 2; i++)
		{
			s[0]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey1);
			s[1]->checkOnBoard(&stopSnake2, &stopSnake1, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey1);
			for (int j = 2; j < 5; j++)
				objects[j]->checkOnBoard(&stopSnake1, &stopSnake2, indexMission, countNumbers, mission, &isGameOver1, &isGameOver2, countKey1);
			if (stopSnake1 == true)
				pause0 = true;
			else if (stopSnake2 == true)
				pause1 = true;
		}
		
		if ((isGameOver1) || (isGameOver2))
			key = ESC;

		s[0]->stuckObjects(stopSnake1, stopSnake2);
		s[1]->stuckObjects(stopSnake1, stopSnake2);
		if (stopSnake1 == true)
			pause0 = true;
		else if (stopSnake2 == true)
			pause1 = true;

		if ((s[0]->getSnakeCounter() > 0) && (s[0]->getSnakeCounter() < 5))
			pause0 = true;
		if ((s[1]->getSnakeCounter() > 0) && (s[1]->getSnakeCounter() < 5))
			pause1 = true;

		if ((pause0 == true) && (pause1 == true))//snake-s[1]  stop and s[0] stop 
		{
			if (s[0]->getSnakeCounter() == 0)
				s[0]->removeSnake();
			else
				pause0 = false;
			if (s[1]->getSnakeCounter() == 0)
				s[1]->removeSnake();
			else
				pause1 = false;
		}
		else if ((pause1 == true) && (pause0 == false))//snake-s[1]  stop and s[0] move 
		{
			if (s[1]->getSnakeCounter() == 0)
				s[1]->removeSnake();
			else
				pause1 = false;

			s[0]->move();
		}
		else if ((pause0 == true) && (pause1 == false))//snake-s[0]  stop and s[1] move 
		{
			if (s[0]->getSnakeCounter() == 0)
				s[0]->removeSnake();
			else
				pause0 = false;

			s[1]->move();
		}
		else
		{
			pause0 = false;
			s[0]->move();
			pause1 = false;
			s[1]->move();
		}
		countKey1++;

		Sleep(150);

		gotoxy(2, 1);
		setTextColor(LIGHTMAGENTA);
		cout << "Bullets: " << s[1]->getNumBullets();

		gotoxy(69, 1);
		setTextColor(YELLOW);
		cout << "Bullets: " << s[0]->getNumBullets();

	} while (countKey1 != countKey);
}


void TheSnakesGame::setReplayNum() 
{
	replayNum.erase(replayNum.begin(), replayNum.end());
	for (int i = 0; i < logSize; i++)
	{
		arrOfNum[i].counter = 0;
		replayNum.push_back(arrOfNum[i]);
		//replayNum[i].numOnBoard = arrOfNum[i].numOnBoard;
		//replayNum[i].counter = arrOfNum[i].counter;
		//replayNum[i].length = arrOfNum[i].length;
		//replayNum[i].startPoint.set(arrOfNum[i].startPoint.getX(), arrOfNum[i].startPoint.getY());
	}
	//replayNum.resize(logSize);
}




void TheSnakesGame::saveReplay()
{
	for (int j = 0; j < 2; j++)
	{
		if (!(objects[j]->getOnBoard()))
			objects[j]->appearance(*objects[j]->getPoint());
	}
	if (!(objects[4]->getOnBoard()))
		objects[4]->appearance(*objects[4]->getPoint());
	s[0]->setPositionStart(s[0]->getBody());
	s[1]->setPositionStart(s[1]->getBody());
	for (int i = 0; i < 5; i++)
		objects[i]->setPositionStart(*objects[i]->getPoint());
	s[0]->setReplaySnakeCounter(s[0]->getSnakeCounter());
	s[1]->setReplaySnakeCounter(s[1]->getSnakeCounter());
	setReplayNum();
	keys.erase(keys.begin(), keys.end());
	timeKey.erase(timeKey.begin(), timeKey.end());
	s[0]->setIReappearance();
	s[1]->setIReappearance();
	s[0]->setReplayDirection();
	s[1]->setReplayDirection();
}