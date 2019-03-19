#include "MissionMinMax.h"

bool MissionMinMax::solveMinMax(int num, Numbers* numArr, int size)
{
	int temp;
	for (int i = 0; i < size; i++)
	{
		temp = numArr[i].getVal();
		if (isMin && (num > temp))	//check if theres a lower number in array
			return false;
		else if (!isMin && (num < temp))//check if theres a higher number in array
			return false;
	}
	return true;
}

void MissionMinMax::setMission()
{
	int res = rand() % 2;
	string str, dummy;

	if (res == 0)
		isMin = true;
	else
		isMin = false;

	if (isMin)
		str = buildDisplayStr(missionStr, "minimum", dummy);
	else
		str = buildDisplayStr(missionStr, "maximum", dummy);

	updateString(str);
}
