#include"QExercise.h"


void QExercise::setDetails(string _details, int min, int max)
{
	randomNumbers(min, max);
	_details = buildExercise();
	Questions::setDetails(_details, min, max);
}



bool QExercise::IsRightAnswer(int number)
{
	if (missingNum == number)
		return true;
	else
		return false;
}



bool QExercise::isInteger()
{
	double calculate = 0;
	srand((int)time(NULL));
	if (op2 == "*")
	{
		calculate = checkOp(op2, num[1], num[2]);
		calculate = checkOp(op1, num[0], calculate);
	}
	else if (op2 == "/")
	{
		if (op1 == "/")
		{
			calculate = checkOp(op1, num[0], num[1]);
			calculate = checkOp(op2, calculate, num[2]);
		}
		else
		{

			calculate = checkOp(op2, num[1], num[2]);
			calculate = checkOp(op1, num[0], calculate);
		}
	}
	else
	{
		calculate = checkOp(op1, num[0], num[1]);
		calculate = checkOp(op2, calculate, num[2]);
	}

	num[3] = (int)calculate;
	do {
		if ((calculate > 170) || (calculate < 0))
			missing = rand() % 3;
		else
			missing = rand() % 4;
	} while (num[missing] > 169);

	missingNum = num[missing];

	return (fmod(calculate, 1) == 0);
}



double QExercise::checkOp(string op, double num1, double num2)
{
	double calculate;

	if (op == "+")
		calculate = (double)(num1 + num2);
	else if (op == "-")
		calculate = (double)(num1 - num2);
	else if (op == "*")
		calculate = (double)(num1 * num2);
	else// (op == '/')
		calculate = (double)(num1 / num2);

	return calculate;

}



void QExercise::randomNumbers(int min, int max)
{
	int index1, index2;
	char OpArr[4] = { '+','-','/','*' };
	int i;
	srand((int)time(NULL));

	do {
		index1 = rand() % 4;
		op1 = OpArr[index1];
		index2 = rand() % 4;
		op2 = OpArr[index2];
		if (OpArr[index1] == '/')
		{
			if (min == 0)
				min++;
			num[1] = min + rand() % (max - min) + 1;
			if (OpArr[index2] == '/')
			{
				num[2] = min + rand() % (max - min) + 1;
				num[0] = (rand() % 5 + 1)*num[2] * num[1];
			}
			else
			{
				num[0] = (rand() % 10 + 1)*num[1];
				num[2] = min + rand() % (max - min) + 1;
			}
		}
		else if ((OpArr[index2] == '/') && (OpArr[index1] != '/'))
		{
			if (min == 0)
				min++;
			num[2] = min + rand() % (max - min) + 1;
			num[1] = (rand() % 10 + 1) * num[2];
			num[0] = min + rand() % (max - min) + 1;
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				num[i] = min + rand() % (max - min) + 1;
			}
		}
	} while (!isInteger());

}


string QExercise::buildExercise()
{
	int Count[4] = { 0,0,0,0 };
	int generalCount = 0;//Counting the amount of general digit
	int i, j, s = 0;
	string exercise;
	for (i = 0; i < 4; i++)
		if (i != missing)
		{
			Count[i] += countDigit(num[i]);
			generalCount += Count[i];
		}

	
	i = 0;


	for (j = 0; j < 7; j++)
	{
		if (j % 2 == 0)
		{
			
			if (i != missing)
				exercise.append(to_string(num[i]));
			else
				exercise.append("_");
			i++;


		}
		else
		{
			if (j == 1)
				exercise.append(op1);
			else if (j == 3)
				exercise.append(op2);
			else //(j == 5)
				exercise.append("=");
		}
	}

	return exercise;
}