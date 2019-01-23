#ifndef _QPRIME_H_
#define _QPRIME_H_

#include "Questions.h"


class QPrime :public Questions
{
	int num;
public:
	virtual void setDetails(string _details, int min, int max);
	virtual void randomNumbers(int min, int max);
	virtual bool IsRightAnswer(int number);
};
#endif // !_QPRIME_H_
