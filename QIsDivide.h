#ifndef _QISDIVIDE_H_
#define _QISDIVIDE_H_

#include "Questions.h"


class QIsDivide :public Questions
{
	int div;
	int remaining = 0;
public:
	virtual void setDetails(string _details, int min, int max);
	virtual bool IsRightAnswer(int number);
	virtual void randomNumbers(int min, int max);
};

#endif // !_QISDIVIDE_H_

