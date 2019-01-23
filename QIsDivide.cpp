#include "QIsDivide.h"



bool QIsDivide::IsRightAnswer(int number)
{
	if (number%div == remaining)
		return true;
	else
		return false;
}

void QIsDivide::setDetails(string _details, int min, int max)
{
	int i = _details.find("X");
	_details.erase(i, 1);
	randomNumbers(min, max);
	_details.insert(i, to_string(div));
	i = _details.find_last_of("Y");
	_details.erase(i, 1);
	_details.insert(i, to_string(remaining));
	Questions::setDetails(_details, min, max);
}



void QIsDivide::randomNumbers(int min, int max)
{
	srand((int)time(NULL));
	if (min == 0)
		min++;
	div = min + rand() % (max - min) + 1;
	do {
		remaining = min + rand() % (max - min) + 1;
	} while (div <= remaining);
}