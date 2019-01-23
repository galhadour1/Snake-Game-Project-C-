#ifndef _QEXERCISE_H_
#define _QEXERCISE_H_

#include "Questions.h"


class QExercise :public Questions
{
	int num[4];
	int missing;//this is the index of the missing number
	string op1, op2;
	double missingNum;
public:
	virtual void setDetails(string _details, int min, int max);
	virtual void randomNumbers(int min, int max);
	virtual bool IsRightAnswer(int number);
	bool isInteger();
	double checkOp(string op, double num1, double num2);
	string buildExercise();
};
#endif // !_QEXERCISE_H_