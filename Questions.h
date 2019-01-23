#ifndef _QUESTIONS_H_
#define _QUESTIONS_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include "Color.h"
#include "io_utils.h"

using namespace std;

class Questions
{
	string details;
public:
	virtual void setDetails(string _details, int min, int max);
	virtual void print();
	virtual bool IsRightAnswer(int number) = 0;
	int countDigit(int num);
};
#endif // !_QUESTIONS_H_

