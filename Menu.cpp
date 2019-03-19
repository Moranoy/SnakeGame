#include <iostream>
#include "Menu.h"
#include "io_utils.h"
#include <string.h>
#include <fstream>
using namespace std;

string Menu::getMainMenu(bool instructions, int index)
{
	switch (index)
	{
	case 0:
		if (instructions)
			mainMenu[index].insert(0, "Your target is to eat a number that is a correct answer to the question above.  ");
		else
			mainMenu[index].insert(0, "Choose 1: Show orders                                                           ");
		break;
	case 1:
		if (instructions)
			mainMenu[index].insert(0, "Press  2:Start Game                                                              ");
		else
			mainMenu[index].insert(0, "       2: Start new game                                                        ");
		break;
	case 2:
		if (instructions)
			mainMenu[index].insert(0, "       3: Exit                                                                 ");
		else
			mainMenu[index].insert(0, "       3: Exit                                                                 ");
		break;
	case 3:
			mainMenu[index].insert(0, "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~");
		break;
	default:
		break;
	}
	return mainMenu[index];
}

void Menu::updateGameMenu(bool isnewQuestion)
{
	deleteAllGameMenus(true);
	gotoxy(0, 0);
	if (isnewQuestion)
		setNewQuestion();
	else
		resumeQuestion();//resume question
	printMenu();
}

void Menu::setNewQuestion()
{
	missionIndex = rand() % numOfMissions;

	missionBank[missionIndex]->setMission();
	string text = missionBank[missionIndex]->getText(); //new question

	gameMenu[0].clear();
	gameMenu[0].insert(0, text, 0, text.size());
}
string Menu::getGameMenu(int index, bool chooseQuestion, Numbers* numArr)
{
	if (index == 0)
		if (chooseQuestion)
		{
			gameMenu[index].clear();
			deleteGameMenu(index);
			setNewQuestion();
		}
	return gameMenu[index];
}

void Menu::displayMenuScreen(bool start, bool instructions, bool newQuestion, char keyPressed, char screenMenu[][SCREEN_COLS], Numbers* numArr)
{
	string screen, str;
	bool chooseQuestion = true;
	if (keyPressed == KEYS::ESC && start == true)	//set secondary menu
	{
		chooseQuestion = false;
		setSecondaryGameMenu();
		for (int i = 0; i < MENU_ROWS; i++)
			memcpy(screenMenu[i], gameMenu[i].c_str(), gameMenu[i].size());
	}
	else
	{
		int len;
		for (int i = 0; i < MENU_ROWS; i++)
		{
			if (!start) //main menu
				screen = getMainMenu(instructions, i);
			else if (newQuestion)
				screen = getGameMenu(i, chooseQuestion, numArr);

			len = screen.size();
			if (len > SCREEN_COLS)
				len = SCREEN_COLS;
			memcpy(screenMenu[i], screen.c_str(), len);
		}
	}
	setTextColor(Color::LIGHTGREY);
	for (int i = 0; i < MENU_ROWS; i++)
	{
		gotoxy(0, i);
		
		for (int j = 0; j < (int)strlen(screenMenu[i]) && j < SCREEN_COLS; j++)
		{
			if (start)
			{
				if (j < (int)gameMenu[i].size())
					cout << screenMenu[i][j];
				else
					cout << EMPTY_CHAR;
			}
			else
			{
				if (j < (int)mainMenu[i].size())
					cout << screenMenu[i][j];
				else
					cout << EMPTY_CHAR;
			}
		}
		cout << endl;
	}
	setTextColor(Color::WHITE);
}

void Menu::deleteAllGameMenus(bool fromScreenAlso)
{
	for (int i = 0; i < MENU_ROWS - 1; i++)
	{
		deleteGameMenu(i);
		if (fromScreenAlso)
		{
			gotoxy(0, i);
			cout << "                                                                               ";
		}
	}
}

void Menu::deleteGameMenu(int index)
{
	gameMenu[index].clear();
}

void Menu::setSecondaryGameMenu()
{
	deleteGameMenu(0); //delete first row
	gameMenu[0].insert(0,"Press 1:Exit, 2:Back To Main Menu, 3:Resume Game, 4:Start over task"); //need to write the orders to game
	gameMenu[1].insert(0, "5:Start new task, 6:Start new game, 7:Replay");
	gameMenu[2].clear();
}

void Menu::resumeQuestion()
{
	string text = missionBank[missionIndex]->getText(); //in case we have a data member of the mission text
	gameMenu[0].insert(0, text);
}

void Menu::printMenu()
{
	setTextColor(Color::LIGHTGREY);
	for (int i = 0; i < MENU_ROWS; i++)
	{
		gotoxy(0, i);
		cout << gameMenu[i];
	}
	setTextColor(Color::WHITE);
}

void Menu::printCorrectAnswer(bool isRightAns, char snakeType, bool isGameOver)
{
	char c = snakeType;
	gotoxy(MESSAGE_POSITION, MESSAGE_ROW);
	if (isGameOver)
	{
		for (int i=0; i < MESSAGE_POSITION/ MESSAGE_ROW; i++)
		{
			gotoxy(MESSAGE_POSITION, MESSAGE_ROW);
			setTextColor(Color::LIGHTMAGENTA);
			cout << "The " << c << " snake won the Game! Congratulation! :) ";
			gotoxy(MESSAGE_POSITION, MESSAGE_ROW);
			setTextColor(Color::LIGHTCYAN);
			cout << "The " << c << " snake won the Game! Congratulation! :) ";
		}
		sound.playGameOver();
	}
	else
	{
		if (isRightAns)
		{
			setTextColor(Color::LIGHTGREEN);
			sound.playSoundCorrect();
			cout << "The " << c << " snake correct :)            ";
		}
		else
		{
			setTextColor(Color::LIGHTRED);
			cout << "The " << c << " snake is incorrect :(       ";
			sound.playSoundFail();
		}
	}
	setTextColor(Color::WHITE);
}

void Menu::printNoMoreShotsMessage(char snakeType)
{
	gotoxy(MESSAGE_POSITION, MESSAGE_ROW);
	setTextColor(Color::LIGHTRED);
	cout << "The " << snakeType << " doesn't have any more shots!";
}

void Menu::printSnakeHitsNumEater(char snakeType)
{
	gotoxy(MESSAGE_POSITION, MESSAGE_ROW);
	setTextColor(Color::LIGHTRED);
	gameMenu[MESSAGE_ROW].clear();
	cout << "The NumEater hits the " << snakeType << " snake!";
	sound.playSoundFail();
	setTextColor(Color::WHITE);
}

void Menu::updateSnakesMessageRow(int snakeIndex, int size, int shotsCounter)
{
	string s;
	if (snakeIndex == 0) //total 30 indecies
	{
		setTextColor(Color::CYAN);
		s = "Snake @: size=";
		gotoxy(0, 1);
		cout << s;
	}
	else
	{
		setTextColor(Color::YELLOW);
		s = "Snake #: size=";
		gotoxy(45, 1);
		cout << s;
	}

	cout << size << ", ";
	if (size < 10) //in case the snake's size is 1 digits
		cout << " ";
	cout << "shots left=" << shotsCounter;
	setTextColor(Color::WHITE);
	
}

bool Menu::isNumberCorrect(int number, Numbers* numArr, int arraySize)
{
		return missionBank[missionIndex]->solveProblem(number);
}

void Menu::loadMissionBank() //load mission texts from file
{
	vector <Mission*>::iterator itrStart = missionBank.begin();
	string token, line;
	size_t pos = 0;
	int index = 0;
	ifstream missionFile("Missions.txt");
	if (!missionFile.is_open())
		cout << "Can't open the file";
	else
	{
		while (!missionFile.eof())
		{
			getline(missionFile, line);
			while ((pos = line.find(",")) != std::string::npos)
			{
				token = line.substr(0, pos);
				line.erase(0, pos + 1);
				setMissionInBanktByType(token, line);
				index++;
			}
		}
		missionFile.close();	
	}

	numOfMissions = index;
}
void Menu::setMissionInBanktByType(string str, string line)
{
	Mission* mission = nullptr;

	if (str.find("DIVIDE") != string::npos)
		mission = new MissionDivide();
	else if (str.find("GRTLT") != string::npos)
		mission = new MissionGrtLt();
	else if (str.find("ODDEVEN") != string::npos)
		mission = new MissionOddEven();
	else if (str.find("POWER") != string::npos)
		mission = new MissionPow();
	else if (str.find("EQUATION") != string::npos)
		mission = new MissionAssignments();

	if (mission != nullptr)
	{
		mission->setMissionText(&line[0]);
		missionBank.push_back(mission);
	}
}