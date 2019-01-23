#include <iostream>
#include <string>
#include"TheSnakesGame.h"
#include "GameManager.h"
#include "_board.h"
#include "Missions.h"

#include "Color.h"
#include  "Snake.h"

void GameManager::mainMenu()
{
	PlaySound(L"AD-FinalCountdown_pt2.wav", NULL, SND_FILENAME | SND_ASYNC);
	setTextColor(LIGHTCYAN);
	
	cout << "(1) view the instructions\n";
	cout << "(2) start the game\n";
	cout << "(9) get out of the game\n";
	
	char selection = 0;
	do {
		selection = _getch();
	} while (!GameManager::isValidOption(selection));

}
bool GameManager::isValidOption(char selection)
{
	char ch;
	int indexMission = -1;


	switch (selection)
	{
	case '1':
	{

		ch = Instructions();
		return 1;
		break;
	}
	case '2':
	{
		system("cls");
		TheSnakesGame game;
		Missions mission;
		bool pause0 = false, pause1 = false;
		bool replay = false;
		game.setBoard(board_example);
		int countKey = 0, count = 0, countNumbers = 0;
		game.init(6);
		indexMission = mission.printMission(indexMission);


		game.run(indexMission, mission, pause0, pause1,replay, countKey, count, countNumbers);
		mission.deleteMissions();
		return 1;
		system("cls");
		break;
	}
	case '9':
	{
		PlaySound(L"bye-bye-4.wav", NULL, SND_FILENAME | SND_ASYNC);

		system("cls");
		setTextColor(LIGHTCYAN);
		gotoxy(1, 2);
		cout << "\t\t\t\t******************************\n\n";
		cout << "\t\t\t\t         GOOD BYE!! ^_^\n\n";
		cout << "\t\t\t\t******************************\n";
		Sleep(1000);
		return 1;
		break;
	}
	default:
	{
		return 0;
		break;
	}
	}

}

char GameManager::Instructions()
{
	
	clear_screen();
	char ch;
	cout << "\n\t\t Instructions" << endl << endl;
	cout << "Controls:" << endl;
	cout << "   Snake 1 controls: \n\tUp-w\n\tDown-x\n\tRight-d\n\tLeft-a " << endl;
	cout << "   Snake 2 controls:\n\tUp-i\n\tDown-m\n\tRight-l\n\tLeft-j" << endl;
	cout << "Goal:\n   The winner of the game is the first player that reached to 12 points.\n" << endl;
	cout << " The player needs to move in the screen to get the right number/s according to the mission that appears on the screen." << endl;
	cout << " if the player gets the right number his snake will grow and he will get 1 point"<<endl;
	cout << " if the player gets the wrong number the other player will get 1 point" << endl;
	cout << " If both players did not solve the mission and there are 60 numbers on the screen," << endl;
	cout << " the game will stop and a appropriate message will appear\n" << endl;

	cout << "Main menu press-esc" << endl;
	ch = _getch();
		if (ch==27)
		{
			system("cls");
			mainMenu();
		}
	

	
	return ch;
}


void GameManager::SecondaryMenu(TheSnakesGame* game, int indexMission, Missions mission ,bool &pause0, bool &pause1, int &countKey, int &count, int &countNumbers)
{
	PlaySound(L"AD-FinalCountdown_pt2.wav", NULL, SND_FILENAME | SND_ASYNC);
	char selection = 0;
	setTextColor(LIGHTCYAN);
	cout << "(1) get out of the game\n";
	cout << "(2) back to the main menu\n";
	cout << "(3) resume game\n";
	cout << "(4) restart the mission\n";
	cout << "(5) start new mission\n";
	cout << "(6) start new game\n";
	cout << "(7) replay the mission\n";

	do {
		selection = _getch();
	} while (!GameManager::isValidOption2(selection, game, indexMission, mission,pause0, pause1, countKey, count, countNumbers));

}

bool GameManager::isValidOption2(char selection, TheSnakesGame* game, int indexMission, Missions mission, bool &pause0, bool &pause1, int &countKey, int &count, int &countNumbers)
{
	bool replay = false;
	
	switch (selection)
	{
	case '1':
	{

		PlaySound(L"bye-bye-4.wav", NULL, SND_FILENAME | SND_ASYNC);

		system("cls");
		setTextColor(LIGHTCYAN);
		gotoxy(1, 2);
		cout << "\t\t\t\t******************************\n\n";
		cout << "\t\t\t\t         GOOD BYE!! ^_^\n\n";
		cout << "\t\t\t\t******************************\n";
		Sleep(1000);
		return 1;
		break;
	}
	case '2':
	{
		system("cls");
		mainMenu();
		return 1;
		break;
	}
	case '3':
	{
		system("cls");
		setTextColor(WHITE);
		game->init(3);
		
		indexMission= mission.printReplayMission();
		
		game->run(indexMission,mission, pause0, pause1,replay, countKey, count, countNumbers);
		return 1;
		break;
	}
	case '4':
	{
		system("cls");
		game->setBoard(board_example);

		game->init(4);
		game->removeAllArr();
		
		indexMission = mission.printReplayMission();
		game->restartBullets();
		pause0 = false;
		pause1 = false;
		game->saveReplay();
		countKey = 0;
		count = 0;
		game->run(indexMission, mission, pause0, pause1,replay, countKey, count,countNumbers);

		
		
		
		return 1;
		break;
	}
	case '5':
	{
		system("cls");
		game->setBoard(board_example);

		game->init(5);
		game->removeAllArr();
		
		countNumbers = game->startNewMission(countNumbers, &indexMission, mission, countKey);
		game->restartBullets();
		pause0 = false;
		pause1 = false;

		countKey = 0;
		count = 0;

		game->run(indexMission, mission, pause0, pause1,replay, countKey, count, countNumbers);

		return 1;
		
		break;
	}
	case '6':
	{
		system("cls");
		game->setBoard(board_example);

		game->init(6);
		game->removeAllArr();
		
		
		indexMission= mission.printMission(indexMission);
		game->restartBullets();
		pause0 = false;
		pause1 = false;
		game->saveReplay();
		countKey = 0;
		count = 0;
		countNumbers = 0;
		game->run(indexMission, mission, pause0, pause1,replay, countKey, count, countNumbers);

		return 1;
		
		break;
	}
	case '7':
	{
		system("cls");

		game->init(7);
		game->removeAllArr();
		indexMission = mission.printReplayMission();
		game->restartBullets();
		pause0 = false;
		pause1 = false;
		replay = true;
		game->run(indexMission, mission, pause0, pause1, replay, countKey,count,countNumbers);


		return 1;
		break;
	}
	default:
	{
		system("cls");
		SecondaryMenu(game, indexMission, mission, pause0, pause1, countKey, count, countNumbers);
		return 1;
		break;
	}

	}

}

void GameManager::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}



