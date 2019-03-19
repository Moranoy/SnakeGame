#ifndef _MISSIONMINMAX_H_
#define _MISSIONMINMAX_H_
#include "Mission.h"
#include "Numbers.h"

class MissionMinMax :public Mission {
	bool isMin;
	string missionStr;
public:

	bool solveMinMax(int num, Numbers* numArr, int size);
	virtual void setMission() override;
	virtual void setMissionText(char* line) override { missionStr = line; }
	virtual bool solveProblem(int num) override { return false; }
	bool getIsMin() { return isMin; }

};

#endif
