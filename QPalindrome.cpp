#include"QPalindrome.h"


void QPalindrome::setDetails(string _details, int min, int max)
{
	Questions::setDetails(_details, min, max);
}



bool QPalindrome::IsRightAnswer(int number)
{
	int newNum = 0, num = number;
	while (num > 0)
	{
		newNum = (newNum * 10) + (num % 10);
		num = num / 10;
	}
	return(newNum == number);
}



