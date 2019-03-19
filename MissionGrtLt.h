#ifndef _MISSIONGRTLT_H_
#define _MISSIONGRTLT_H_
#include "Mission.h"

class MissionGrtLt :public Mission {
	int randNum1, randNum2; //num 1 > num 2
	string missionStr;
public:
	//	string getText() { return text; }
	string getText() { return "greater/less than "; }
	virtual bool solveProblem(int num) override;//add override
	virtual void setMission() override;
	virtual void setMissionText(char* line) override { missionStr = line; }

};

#endif
