#ifndef _MISSIONODDEVEN_H_
#define _MISSIONODDEVEN_H_
#include "Mission.h"

class MissionOddEven :public Mission {
	bool isOdd;
	string missionStr;
public:

	virtual bool solveProblem(int num) override; //add override
	virtual void setMission() override;
	virtual void setMissionText(char* line) override { missionStr = line; }

};

#endif