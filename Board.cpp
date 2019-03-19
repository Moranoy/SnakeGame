#include "Board.h"
void Board::setAndDrawPoint(int x, int y, char c) 
{
	drawPoint(x, y, c);
	screenGame[y][x] = c;
}

void Board::drawPoint(int x, int y, char c)
{
	gotoxy(x, y);
	cout << c;
}

void Board::deleteTail(int rowInd, int colInd)
{
	setAndDrawPoint(colInd, rowInd, EMPTY_CHAR);
}

void Board::drawYourself()
{
	for (int y = 0; y < GAME_ROWS; y++)//y
		for (int x = 0; x < SCREEN_COLS; x++)//x
			drawPoint(x, y+MENU_ROWS, screenGame[y][x]);
	gotoxy(0, 0);
}

void Board::resetBoard()
{
	for (int i = 0; i < GAME_ROWS; i++)
		for (int j = 0; j < SCREEN_COLS; j++)
			screenGame[i][j] = EMPTY_CHAR;
}
