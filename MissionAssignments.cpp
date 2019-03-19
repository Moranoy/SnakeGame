#include "MissionAssignments.h"

const char* MissionAssignments::createNewAssignments()
{
	int i;
	double tempRes = 0;
	OpType opInd;
	bool isResInt = false;
	currAssignmentStr.clear(); //clear string
	
	while(!isResInt)
	{
		missingNumInd = rand() % (NUM_OF_NUMBERS - 1); //rand which number will be missing
		for (i = 0; i < NUM_OF_OPERATORS; i++) //rand operators
		{
			opInd = (OpType)(rand() % OPTIONAL_OPERATORS);
			if (opInd == add)
				operatorsArr[i] = ADD;
			else if (opInd == sub)
				operatorsArr[i] = SUB;
			else if (opInd == multiply)
				operatorsArr[i] = MULTIPLY;
			else 
				operatorsArr[i] = DIV; 
		}
		for (i = 0; i < NUM_OF_NUMBERS; i++)
			numbersArr[i] = 0;
		getNumbersArr();

		tempRes = calculateTheResult(numbersArr[missingNumInd]); //calculate res (num 4) using the numbers array 
		if (tempRes == CALC_ERROR)	//dividing  by 0
			continue;

		bool validNums = tempRes - (int)tempRes == 0 && numbersArr[missingNumInd] <= MAX_NUM_VAL && numbersArr[missingNumInd] >= 0 && numbersArr[missingNumInd] - (int)numbersArr[missingNumInd] == 0 && tempRes >= -50 && tempRes <= 200;
		if (validNums)						//check if resault is an int 
			isResInt = true;				// and if missing num is in range
										
	}
	numbersArr[NUM_OF_NUMBERS - 1] = (int)tempRes;
	uniteAssignment();
	updateString(currAssignmentStr);
	return currAssignmentStr.c_str();
}

void MissionAssignments::getNumbersArr()
{
	size_t currIndex = 0;
	bool setLastNum = false;

	if(operatorsArr[0] == MULTIPLY) 
	{ 
		mult2Nums(currIndex);
		setLastNum = true;
	}
	else if (operatorsArr[0] == DIV)
	{
		setLastNum = true;
		div2Nums(currIndex);
	}
	else if (operatorsArr[1] == MULTIPLY)
	{
		numbersArr[currIndex++] = rand() % LOW_NUM_VAL;
		mult2Nums(currIndex);
	}
	else if(operatorsArr[1] == DIV)
	{
		numbersArr[currIndex++] = rand() % LOW_NUM_VAL;
		div2Nums(currIndex);
	}
	else if (operatorsArr[1] == ADD || operatorsArr[1] == SUB) //no division and no multiplication
	{
		numbersArr[currIndex++] = rand() % LOW_NUM_VAL;
		numbersArr[currIndex++] = rand() % LOW_NUM_VAL;
		numbersArr[currIndex++] = rand() % LOW_NUM_VAL;
	}

	if(setLastNum == true)
	{ 
		
		if (operatorsArr[1] == MULTIPLY)
			numbersArr[currIndex] = LOWER_NUM_VAL;
		else if (operatorsArr[1] == DIV)
			divLastNum();
		else
			 numbersArr[currIndex] = rand() % LOW_NUM_VAL;
	}
}

void MissionAssignments::mult2Nums(size_t& ind)
{
	numbersArr[ind++] = rand() % LOWER_NUM_VAL; //set lower values for multiplication
	numbersArr[ind++] = rand() % LOWER_NUM_VAL;
}
void MissionAssignments::div2Nums(size_t& ind)
{
	bool validDiv = false;
	double divRes;

	while (validDiv == false)
	{
		numbersArr[ind] = rand() % LOW_NUM_VAL;
		if(numbersArr[ind] == 0)
			numbersArr[ind + 1] = (rand() % LOW_NUM_VAL) + 1; //get rand num, doesnt matter cause 0/x = 0 as long as its not 0
		else
			numbersArr[ind + 1] = (rand() % numbersArr[ind]) + 1; //make sure second num isnt 0 with +1, and that the divider num is lower than devided num
		divRes = numbersArr[ind] / (double)numbersArr[ind + 1];
		validDiv = (int)divRes - divRes == 0;						//make sure that res is an int
	}

	ind += 2;
}
void MissionAssignments::divLastNum()
{
	bool isValidDir = false;
	double divRes;

	if(isLeftSideValZero() == true)
		numbersArr[2] = (rand() % LOW_NUM_VAL) + 1; //get a num as long as its not 0
	else
	{
		while (isValidDir == false)
		{
			numbersArr[2] = (rand() % numbersArr[1]) + 1; //make sure last num is lower than prev num, and that divided num is not 0 with +1
			divRes = calcHelper(numbersArr[0], numbersArr[1], operatorsArr[0]) / (double)numbersArr[2];
			isValidDir = (int)divRes - divRes == 0;
		}
	}
}

bool MissionAssignments::isLeftSideValZero()
{
	double res;
	res = calcHelper(numbersArr[0], numbersArr[1], operatorsArr[0]);

	if (res == 0)
		return true;
	else
		return false;
}
double MissionAssignments::calculateTheResult(int ansNum)
{
	double res1, res2;
	int temp = numbersArr[missingNumInd];
	numbersArr[missingNumInd] = ansNum;
	if (numbersArr[1] == 0 && operatorsArr[0] == DIV || numbersArr[2] == 0 && operatorsArr[1] == DIV)
		return CALC_ERROR;

	else if (isLeftFirst() == true)  //left side is first
	{
		res1 = calcHelper(numbersArr[0], numbersArr[1], operatorsArr[0]);
		res2 = calcHelper(res1, numbersArr[2], operatorsArr[1]);
	}
	else							//right side is first
	{
		res1 = calcHelper(numbersArr[1], numbersArr[2], operatorsArr[1]);
		res2 = calcHelper(numbersArr[0], res1, operatorsArr[0]);
	}

	numbersArr[missingNumInd] = temp;
	return res2;
}

bool MissionAssignments::isLeftFirst()
{
	if (!isMultiplyOrDiv(0) && isMultiplyOrDiv(1))
		return false;
	else
		return true;
}
double MissionAssignments::calcHelper(double num1, double num2, char op)
{
	if (op == ADD)
		return num1 + num2;

	else if (op == SUB)
		return num1 - num2;
	
	else if (op == MULTIPLY)
		return num1 * num2;
	
	else
		return num1 / num2;
}

void MissionAssignments::uniteAssignment()
{
	int opInd = 0;
	for (int i = 0; i < NUM_OF_NUMBERS; i++)
	{
		if (i == missingNumInd)							//input numbers into string
			currAssignmentStr += EMPTY_NUM_STR;
		else
			currAssignmentStr += std::to_string(numbersArr[i]);

		if (opInd == 2)									//input operators into string
			currAssignmentStr += "=";									//last operator
		else if(opInd < 2)								
			currAssignmentStr += operatorsArr[opInd];

			opInd++;
	}
}


bool MissionAssignments::solveProblem(int number)
{
	bool res = false;
	double ansRes;
	if (number == numbersArr[missingNumInd])
		res = true;
	else if (isMultiplyOrDiv(0) && isMultiplyOrDiv(1)) //both operators are mul or div, and there is atleast one 0
	{
		for (int i = 0; i<NUM_OF_NUMBERS; i++)
			if (numbersArr[i] == 0)
				res = true;
	}
	else
	{
		ansRes = calculateTheResult(number);
		res = numbersArr[3] == ansRes;
	}
	return res;
}
