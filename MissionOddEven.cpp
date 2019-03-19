#include "MissionOddEven.h"
void MissionOddEven::setMission()
{
	string addedStr1, addedStr2;
	if ((rand() % 2) == 0)
	{
		addedStr1 = "even";
		isOdd = false;
	}
	else
	{
		addedStr1 = "odd";
		isOdd = true;
	}

	string res = buildDisplayStr(missionStr, addedStr1, addedStr2);
	updateString(res);
}

bool MissionOddEven::solveProblem(int num)
{
	if (!isOdd && num % 2 == 0)
		return true;
	else if (isOdd && num % 2 != 0)
		return true;
	return false;
}