#ifndef _MISSIONPOW_H_
#define _MISSIONPOW_H_
#include "Mission.h"
#include <math.h>
#include <string>
class MissionPow :public Mission {
	string missionStr;
	int base, power;
	enum Vals { MaxPow = 3, LowBase = 2, MidBase = 4, HighBase = 12, MinVal = 2 };
	enum Pows { LowPow = 2, MidPow = 3, HighPow = 4 };
public:
	virtual bool solveProblem(int num) override;
	virtual void setMission() override;
	virtual void setMissionText(char* line) override { missionStr = line; }
};

#endif


