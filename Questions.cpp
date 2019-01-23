#include "Questions.h"



void Questions:: setDetails(string _details, int min, int max)
{
	details = _details;
}


void Questions::print() {
	setTextColor(LIGHTCYAN);
	gotoxy(2, 0);
	for (int i = 0; i<79; i++)
		cout << " ";
	gotoxy(2, 0);
	cout << details;
}


int Questions::countDigit(int num)
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