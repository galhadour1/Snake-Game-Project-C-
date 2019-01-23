#include"QSquare.h"


void QSquare::setDetails(string _details, int min, int max)
{
	int i = _details.find("X");
	_details.erase(i, 1);
	randomNumbers(min, max);
	_details.insert(i, to_string(num));
	Questions::setDetails(_details, min, max);
}



bool QSquare::IsRightAnswer(int number)
{
	double squre;
	squre = sqrt(number);
	if (squre == num)
		return true;
	else
		return false;
}



void QSquare::randomNumbers(int min, int max)
{
	srand((int)time(NULL));
	num = min + rand() % (max - min) + 1;
}