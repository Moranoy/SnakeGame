#ifndef _REPLAY_H_
#define _REPLAY_H_
#include <vector>
#include "Numbers.h"
#include "Snake.h"
#include "Menu.h"
using namespace std;

class Replay {
	enum Reserve {Many = 100, Some = 50};
	const char NoKey = 0;
	vector<char> input;
	vector<int> turns;
	vector<Numbers> numbers;
	vector<int> snakeData;
	Snake savedSnakes[SNAKES_ARR_SIZE];
	int inputInd, turnInd, numbersInd, sDataInd;
	bool isInReplay;
	int startingNums;
public:
	Replay();
	void reset(Snake* s);
	char getInput(int turn);
	void saveNumbersOnScreen(Numbers * numArr, int size);
	void getStartingNumbers(Numbers* numArr, int& size);
	void resetIndexes() { inputInd = turnInd = numbersInd = sDataInd  = 0; }
	bool isReplay() { return isInReplay; }
	void addNumber(Numbers& num){ numbers.push_back(num); }
	Numbers getNumber() { return numbers[numbersInd++]; }
	void endOfReplay() { isInReplay = false; }
	void unsaveNumbers() { startingNums = 0; }
	void setInput(char in, int turn)
	{
		input.push_back(in);
		turns.push_back(turn);
	}
	void getSnakeLocation(int& headX, int& headY, Direction& dir, int& sSize);
	void setSnakeLocation(int headX, int headY, Direction dir, int sSize);
	
	void startReplay(Snake* s);

};



#endif