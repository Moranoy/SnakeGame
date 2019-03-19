#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

using namespace std;

#include <Windows.h>
#include <conio.h>
#include "Snake.h"
#include "Menu.h"
#include "Definitions.h"
#include "Board.h"
#include "Numbers.h"
#include "Shot.h"
#include "Flyers.h"
#include "Eater.h"
#include <list>
#include "Replay.h"

class SnakesGame {
	Menu menu;
	Board board;
	Replay replay;
	Numbers numArr[MAX_NUM_ARR_SIZE];
	list<Numbers*> numList;
	Eater numEater = { Point{ Flyers::ROW, Flyers::COL}};
	Flyers rowFlyer1 = { Direction::RIGHT, Point{ Flyers::RF1Col, Flyers::RF1Row }, Color::LIGHTMAGENTA, ROW_FLYER_CHAR, false, true, true },	//row flyers
			 rowFlyer2 = { Direction::LEFT, Point{ Flyers::RF2Col, Flyers::RF2Row }, Color::LIGHTMAGENTA, ROW_FLYER_CHAR, false, false, true },
		     colFlyer1 = { Direction::UP, Point{ Flyers::CF1Col, Flyers::CF1Row }, Color::LIGHTMAGENTA, COL_FLYER_CHAR, true, false, false }, //col flyers
			 colFlyer2 = { Direction::DOWN, Point{ Flyers::CF2Col, Flyers::CF2Row }, Color::LIGHTMAGENTA, COL_FLYER_CHAR, true, true, false };
	int numArrSize = 0;
	int currTurn = 0;
	char screenMenu[MENU_ROWS][SCREEN_COLS];
	bool snakesAreMoving;
	char keyPressed;
	Flyers* flyers[MAX_FLYERS_ARR_SIZE] = { &numEater, &rowFlyer1, &rowFlyer2, &colFlyer1, &colFlyer2 };
	Snake sOriginal[SNAKES_ARR_SIZE] = {
		{ { START_POSITION_COL1, START_POSITION_ROW }, SNAKE_1_CHAR, Color::CYAN, Direction::RIGHT }, // snake 1
		{ { START_POSITION_COL2, START_POSITION_ROW }, SNAKE_2_CHAR, Color::YELLOW,  Direction::LEFT } // snake 2
	};
	Snake s[SNAKES_ARR_SIZE] = {
		{ { START_POSITION_COL1, START_POSITION_ROW }, SNAKE_1_CHAR, Color::CYAN, Direction::RIGHT }, // snake 1
		{ { START_POSITION_COL2, START_POSITION_ROW }, SNAKE_2_CHAR, Color::YELLOW, Direction::LEFT } // snake 2
	};
	
	void initScreen();
	int getHitNumIndex(Point& nextP);
	void resetGame(bool& startGame);

	void drawNumbers();

public:
	SnakesGame() {
		sOriginal[0].setKeys('a', 'd', 'w', 'x', 'z');
		sOriginal[1].setKeys('j', 'l', 'i', 'm', 'n');
		sOriginal[0].changeDir('d'); //move right
		sOriginal[1].changeDir('j');//move left
		s[0].setColor(CYAN);
		s[1].setColor(YELLOW);
		initScreen();
	}
	void run();
	void unPauseSnake(int sIndex);
	void setLegalLocation(int & headX, int & headY, Direction & newDir, int sSize);
	bool isLegalLocationHelper(Direction & newDir);
	bool keyHit(bool & instructions, bool & startGame);
	char getInput();
	void spawnNumber();
	char availableNextMove(int i);
	void eatNum(int index);
	void getStartOfNumPoint(Point & nextPoint, Point& startOfNumPoint);
	void sparklingNumbers(int questionInd);
	void changeNumsColor(Color color, int index);
	bool isNum(char c);
	void deleteNumbers(bool deleteHalf);
	int deleteNum(int& numIndex, Point& nextPoint, Point& startOfNumPoint);
	void randomizeArray();
	void startingPosition();
	void resetHowManyShotsAviable();
	void clearLocation(int headCol, int headRow, Direction headDir, int sSize);
	char checkNextMove(int x, int y);
	int runReplay(bool& replayGame);
	bool executeGameMenu(int index, bool& startGame);
	void resetGameObjects(bool _resetShots, bool _resetFlyers, bool _resetPos, bool _resetNumOfShots, bool endReplay);
	void updateSnakesRow();
	void moveAllShots();
	void updateGameMenu(bool newQuestion);
	void snakeInPunshimet(int sIndex);
	void createNewShot(int sIndex);
	int whichSnakeGotHit(Point& point);
	bool isLegalLocation(int & headX, int & headY, Direction & newDir, int sSize);
	void getTailLocation(int & tailX, int & tailY, int headX, int headY, int newDir, int sSize);
	void shotHitsSnake(int i, Point& point);
	void deleteAllShots();
	int getDigit(int x, int y)
	{
		char c = board.screenGame[y][x];
		if (c == EMPTY_CHAR)
			return DUMMY_INT;
	}
	bool moveAllBullets(bool & moveCols);
	bool moveAllSnakes(bool & exit_flag);
	void setNumArrAnswers();
	bool moveFlyers(bool moveCols);
	void findAndRemoveFromNumList(Numbers number);
	void findAndRemoveFromNumListHelper(Point& numPoint);
	bool moveCurrFlyer(int flyerIndex);
	bool flyerHitSnake(int snakeInd, int flyerIndex);
	void setTargetFromList();
	void updateNumList();
	bool flyerHitsShot(int flyerIndex, const Point& p, int snakeIndex);
	void numEaterHitsSnake(int snakeIndex);
	void resetFlyers();
	void set_isCorrect(Numbers & number);
};



#endif

