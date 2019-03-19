#include "MissionGrtLt.h"
#include <iostream>
#include <string>
void MissionGrtLt::setMission()
{
	randNum2 = (rand() % (MAX_NUM_VAL - 10)) + 10; //10...168
	randNum1 = (rand() % (randNum2 / 2)) + (randNum2 / 2) - 1; //randNum1/2... randNum1 - 1
	string res = buildDisplayStr(missionStr, to_string(randNum1), to_string(randNum2));
	updateString(res);
}

bool MissionGrtLt:: solveProblem(int num) 
{
	if (num > randNum1 && num < randNum2)
		return true;
	else
		return false;
}



