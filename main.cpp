#include <windows.h>
#include <iostream>
using namespace std;
#include <mmstream.h>
#include "TheSnakesGame.h"

#include "GameManager.h"
int main() {
	GameManager game1;
	game1.ShowConsoleCursor(false);
	game1.mainMenu();
}