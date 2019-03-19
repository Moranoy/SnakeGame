#include "MissionDivide.h"

void MissionDivide:: setMission()
{
	randNum1 = (rand() % 10) + 3; //numbers 3...10
	randNum2 = (rand() % randNum1); //numbers 0...randNum1 - 1

	string res = buildDisplayStr(missionStr, to_string(randNum1), to_string(randNum2));
	updateString(res);
}

 bool MissionDivide:: solveProblem(int num)   //add override
{
	if ((num % randNum1) == randNum2)
		return true;
	return false;
}