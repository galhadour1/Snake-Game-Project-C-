#ifndef _QPALINDROME_H_
#define _QPALINDROME_H_

#include "Questions.h"


class QPalindrome :public Questions
{
public:
	virtual void setDetails(string _details, int min, int max);
	virtual bool IsRightAnswer(int number);
};
#endif // !_QPALINDROME_H_
