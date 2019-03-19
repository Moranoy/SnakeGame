#ifndef _BOARD_H_
#define _BOARD_H_

#include "Definitions.h"
#include "Point.h"
#include "Color.h"
#include <Windows.h>
class Board {
	void drawPoint(int x, int y, char c);
public:
	char screenGame[SCREEN_ROWS][SCREEN_COLS] =
     //12345678901234567890123456789012345678901234567890123456789012345678901234567890
	{ "                                                                               ",//0
	  "                                                                               ",//1
	  "                                                                               ",//2
	  "                                                                               ",//3
	  "                                                                               ",//4
	  "                                                                               ",//5
	  "                                                                               ",//6
	  "                                                                               ",//7
	  "                                                                               ",//8
	  "                                                                               ",//9
	  "                                                                               ",//10
	  "                                                                               ",//11
	  "                                                                               ",//12
	  "                                                                               ",//13
	  "                                                                               ",//14
	  "                                                                               ",//15
	  "                                                                               ",//16
	  "                                                                               ",//17
	  "                                                                               ",//18
	  "                                                                               ",//19
	  "                                                                               " };//20 = 23-3
	void setAndDrawPoint(int x, int y, char c);
	void deleteTail(int rowInd, int colInd);
	void resetBoard();
	void drawYourself();
	bool isInvalidLocation(int col, int row) //if not a snake, or shot, return true
	{
		if (screenGame[row][col] == EMPTY_CHAR || (screenGame[row][col] >= '0' && screenGame[row][col] <= '9'))
			return false;
		else
			return true;
	}
};
#endif