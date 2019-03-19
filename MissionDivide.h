#ifndef _MISSIONDIVIDE_H_
#define _MISSIONDIVIDE_H_

#include <string>
#include "Mission.h"

class MissionDivide :public Mission {
	int randNum1 , randNum2 = 0; // default numbers
	string missionStr;
public:
	virtual bool solveProblem(int num) override; //add override
	
	virtual void setMission() override;
	virtual void setMissionText(char* line) override { missionStr = line; }
};

#endif