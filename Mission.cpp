#include "Mission.h"

string Mission::buildDisplayStr(string missionStr, string addedStr1, string addedStr2)
{
	string c = "%", str;
	int find = missionStr.find(c), find2;//get first '%' into find
	str.append(missionStr, 0, find); //insert the begining of the text
	str.append(addedStr1); //insert first rand string
	if (!addedStr2.empty())
	{
		find2 = missionStr.find_last_of(c);//get last '%'
		str.append(missionStr, find + 1, find2 - find - 1);// insert the continue of the text
		str.append(addedStr2);// insert the second rand string
	}
	else
		str.append(missionStr, find + 1, missionStr.size()-find - 1);//inset end of text
	return str;
}