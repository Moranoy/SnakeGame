#include "Replay.h"

Replay::Replay()
{
	input.reserve(Many);	//reserve vector elements
	turns.reserve(Many);
	numbers.reserve(Some);
	resetIndexes();	
}

void Replay::reset(Snake* s)
{
	resetIndexes();	
	turns.clear();
	input.clear();
	numbers.clear();
	snakeData.clear();
	isInReplay = false;
	
	for (int i = 0; i < SNAKES_ARR_SIZE;i++)  //copy snakes at the start of a new "recording"
		savedSnakes[i] = s[i];
}

void Replay::getSnakeLocation(int& headX, int& headY, Direction& dir, int& sSize)
{
	headX = snakeData[sDataInd++];
	headY = snakeData[sDataInd++];
	dir = (Direction)snakeData[sDataInd++];
	sSize = snakeData[sDataInd++];
}

void Replay::setSnakeLocation(int headX, int headY, Direction dir, int sSize)
{
	snakeData.push_back(headX);
	snakeData.push_back(headY);
	snakeData.push_back((int)dir);
	snakeData.push_back(sSize);
}



char Replay::getInput(int turn)
{
	
	if ((inputInd + 1) == input.size() && input[inputInd] == Menu::SecondMenu::_Replay)//if last key is "replay"
		return (char)ESC;
	else if (input[inputInd] == Menu::SecondMenu::_Replay)
	{
		turnInd++;
		inputInd++;
		return Menu::SecondMenu::_Resume;
	}
	else if (!turns.empty() && turns[turnInd] == turn)
	{
		turnInd++;
		return input[inputInd++];
	}
	
	return NoKey;
}

void Replay::saveNumbersOnScreen(Numbers* numArr, int size)	//save numbers on screen in the vector
{
	int i;
	numbers.resize(size);

	for (i = 0; i < size; i++)
		numbers[i] = numArr[i];

	startingNums = i;
}

void Replay::startReplay(Snake* s)
{
	resetIndexes();
	isInReplay = true;
	for (int i = 0; i < SNAKES_ARR_SIZE; i++) //get the snakes from before the replay
		s[i] = savedSnakes[i];
}

void Replay::getStartingNumbers(Numbers* arr, int& size) 
{
	int i;
	size = startingNums;
	for (i = 0; i < size && i < numbers.size(); i++)	//copy numbers from vector to array 
		arr[i] = numbers[i];

	numbersInd = i;
}




