#ifndef _MENU_H_
#define _MENU_H_

#include "MissionDivide.h"
#include "sounds.h"
#include "Definitions.h"
#include "MissionGrtLt.h"
#include "Color.h"
#include "Numbers.h"
#include "MissionOddEven.h"
#include "MissionAssignments.h"
#include "MissionPow.h"
#include "Gotoxy.h"
#include <vector>

class Menu {
	Sounds sound;
	vector <Mission*> missionBank;
	int missionIndex = 0;
	int numOfMissions = 0;
	string mainMenu[MENU_ROWS]= {
		"Choose 1: Show orders                                                          ", // 1
		"       2: Start new game                                                       ", // 2
		"       3: Exit                                                                 ",	// 3
		"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*"}; // 4
	string gameMenu[MENU_ROWS]= {
		"                                                                               ", // 1
		"                                                                               ", // 2
		"                                                                               ", // 3
		"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*"};// 4
public:
	enum MenuOptions { _Instructions = '1', _StartGame = '2', _ExitGame = '3' };
	enum SecondMenu { _Exit = '1', _MainMenu = '2', _Resume = '3', _StartOverMission = '4', _StartNewMission = '5', _RestartGame = '6', _Replay = '7' };
	string getMainMenu(bool instructions, int index);
	void updateGameMenu(bool isnewQuestion);
	void setSecondaryGameMenu();
	void resumeQuestion();
	void printMenu();
	void printCorrectAnswer(bool isRightAns, char snakeType, bool isGameOver);
	void deleteGameMenu(int index);
	void deleteAllGameMenus(bool fromScreenAlso);
	void setNewQuestion();
	string getGameMenu(int index, bool chooseQuestion, Numbers * numArr);
	void displayMenuScreen(bool start, bool instructions, bool newQuestion, char keyPressed, char screenMenu[][SCREEN_COLS], Numbers* numArr);
	void printNoMoreShotsMessage(char snakeType);
	void printSnakeHitsNumEater(char snakeType);
	void updateSnakesMessageRow(int snakeIndex, int size, int shotsCounter);
	bool isNumberCorrect(int number, Numbers* numArr, int arraySize);
	int getMissionInd() { return missionIndex; }
	void setMissionIndex(int index) { missionIndex = index; }
	void loadMissionBank(); //load mission texts from file
	void setMissionInBanktByType(string str, string line);
};

#endif

