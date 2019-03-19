#ifndef _MISSION_H_
#define _MISSION_H_

#include <iostream>
#include <string.h>
#include "Definitions.h"

using namespace std;

class Mission {
protected:
	string text;
public:
	string getText() { return text; }
	void updateString ( string str ) { text = str; } 
	string buildDisplayStr (string missionStr, string addedStr1, string addedStr2);
	virtual bool solveProblem (int num) = 0;
	virtual void setMission () = 0;
	virtual void setMissionText (char* line) = 0;
};
#endif