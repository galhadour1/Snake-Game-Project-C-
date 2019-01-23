#include"QPrime.h"


void QPrime::setDetails(string _details, int min, int max)
{
	int i = _details.find("X");
	_details.erase(i, 1);
	randomNumbers(min, max);
	_details.insert(i,to_string(num));
	Questions::setDetails(_details, min, max);
}



bool QPrime::IsRightAnswer(int number)
{
	if ((number == 1) || (number == 0))
		return false;
	else
	{
		for (int i = 2; i < number; i++)
		{
			if (number % i == 0 && i != number)
				return false;
		}
		if (number < num)
			return true;
		return false;
	}
}



void QPrime::randomNumbers(int min, int max)
{
	srand((int)time(NULL));
	num = min + rand() % (max - min) + 1;
}