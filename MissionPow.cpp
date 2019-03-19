#include "MissionPow.h"

bool MissionPow::solveProblem(int num)
{
	if (pow(base, power) == num)
		return true;
	return false;
}
void MissionPow::setMission()
{
	power = (rand() % MaxPow) + MinVal;	//range: 2...4.   +2 so we dont get x^0 or x^1
	switch (power)
	{
	case LowPow:
		base = (rand() % HighBase) + MinVal; //2...13
		break;
	case MidPow:
		base = (rand() % MidBase) + MinVal; //2...5
		break;
	case HighPow:
		base = (rand() % LowBase) + MinVal; // 2 or 3
		break;
	}
	string res = buildDisplayStr(missionStr, to_string(base), to_string(power));
	updateString(res);
}