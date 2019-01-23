#ifndef _QSQUARE_H_
#define _QSQUARE_H_

#include "Questions.h"


class QSquare :public Questions
{
	int num;
public:
	virtual void setDetails(string _details, int min, int max);
	virtual void randomNumbers(int min, int max);
	virtual bool IsRightAnswer(int number);
};
#endif // !_QSQUARE_H_