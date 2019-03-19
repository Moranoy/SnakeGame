#ifndef _ASSIGNMENT_H
#define _ASSIGNMENT_H

#include "Definitions.h"
#include <Windows.h>//random function
#include <iostream>
#include <string>
#include "Mission.h"

class MissionAssignments: public Mission {
	enum Vals {LOWER_NUM_VAL = 5, LOW_NUM_VAL = 25};
	enum MathSizes { NUM_OF_OPERATORS = 2, NUM_OF_NUMBERS = 4, OPTIONAL_OPERATORS = 4 };
	enum OpType { add, sub, multiply, divide };

	int numbersArr[NUM_OF_NUMBERS] = {0,0,0,0};
	char operatorsArr[NUM_OF_OPERATORS] = { ' ', ' '};
	int  missingNumInd;
	std::string currAssignmentStr;	//change 

	bool isLeftSideValZero();
	double calculateTheResult(int ansNum);
	bool isLeftFirst();
	double calcHelper(double num1, double num2, char op);
	int getNum(int index) { return numbersArr[index]; }
	void setNum(int index, int num) { numbersArr[index] = num; }
	char getOperator(int index) { return operatorsArr[index]; }
	void setOperator(int index, char op) { operatorsArr[index] = op; }
	static char* convertStrToChar(std::string& str) { return &str[0]; }
	void uniteAssignment();
	void getNumbersArr();
	void mult2Nums(size_t & ind);
	void div2Nums(size_t & ind);
	void divLastNum();
	 

public:
	string getText() { return currAssignmentStr; }
	const char* createNewAssignments();
	const char * getCurrAssignment() { return currAssignmentStr.c_str(); }
	bool isMultiplyOrDiv(int index)  { return operatorsArr[index] == MULTIPLY || operatorsArr[index] == DIV; }
	virtual bool solveProblem(int num) override;
	virtual void setMission() override { createNewAssignments(); }
	virtual void setMissionText(char* line) override {}
};


#endif
