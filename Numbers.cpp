#include "Numbers.h"

bool Numbers::isEqual(Numbers& other)
{
	Point p;
	p = this->getNumPoint();
	if ((p.isEqual(other.getNumPoint())) && (this->getVal() == other.getVal()))
		return true;
	return false;
}
void Numbers::randNumber(Board& board)
{
	int number, x, y;
	RangeType rangeIndex;
	bool notAviable = true;
	rangeIndex = (RangeType)(rand() % RANGE_TYPE_NUMBER);

	switch (rangeIndex) { //rand number from different ranges
	case RangeType::low:
		number = rand() % 26;
		break;
	case RangeType::medium:
		number = (rand() % 56) + 25;
		break;
	case RangeType::high:
		number = (rand() % 88) + 81;
		break;
		}
	
	while (notAviable)
	{
		y = (rand() % GAME_ROWS) + MENU_ROWS + 1; //rand row
		x = rand() % (SCREEN_COLS - 1); //rand col
		if (checkAviablePoint(x, y, board, number))
			notAviable = false;
	}
	num = number;
	p.setXY(x, y); 

	drawNumber(board);
}

void Numbers::drawNumber(Board& board)
{
	int i, number = num, x,y;
	
	p.getXY(x, y);
	howManyDigits(num);
	for (i = digits; i > 0; i--) //save number on board
	{
		board.screenGame[y][x + i - 1] = char((number % 10) + '0');
		number = number / 10;
	}
	setTextColor(Color::WHITE);
	gotoxy(x, y);

	for (i = 0; i < digits; i++) //print rand number on screen
		cout << board.screenGame[y][x + i];
}


bool Numbers::checkAviablePoint(int x, int y, Board& board, int number)
{
	int i;
	howManyDigits(number);
	if ((digits == 2 && x == SCREEN_COLS-2) || (digits == 3 && x >= SCREEN_COLS - 4)) //check avaible point for digits
		return false;																// -4 cause numbers cant apear close to the borders

	
	for (i = 0; i < digits; i++)
	{

		if (!checkUpDown(x, y+i, board)) //check DUMMY_INTpoints up and down
			return false;
		if (board.screenGame[y][x + i - 1] != EMPTY_CHAR) //check point from the left to the right
			return false;
	}
	if (board.screenGame[y][x + digits] != EMPTY_CHAR) //check 1 to the right of last digit
		return false;
	return true;
}

bool Numbers::checkUpDown(int x, int y, Board& board)
{
	if ((board.screenGame[y - 1][x] != EMPTY_CHAR) || (board.screenGame[y + 1][x] != EMPTY_CHAR))
		return false;
	return true;
}
void Numbers::howManyDigits(int number)
{
	if (number / 10 == 0)
		digits = 1;
	else if (number / 100 == 0)
		digits = 2;
	else
		digits =  3;
}

//erase the number from the board
void Numbers::eraseNumber(Board& board)
{
	Point p, temp;
	int x, y;
	temp.setXY(DUMMY_INT, DUMMY_INT);
	p = this->getNumPoint();
	p.getXY(x, y);
	eraseDigits(board, x, y);

	this->setVal(0); //delete numbers from numArr
	this->setNumPoint(temp);
}

void Numbers::eraseDigits(Board& b, int x, int y)
{
	for (int i = 0; i < digits; i++)
		b.setAndDrawPoint(x + i, y, EMPTY_CHAR);
}

void Numbers::numSwap(Numbers& a)
{
	Numbers temp = *this;
	*this = a;
	a = temp;
}

