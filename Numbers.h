#ifndef _NUMS_H
#define _NUMS_H

#include "Definitions.h"
#include <cstdlib>
#include "Point.h"
#include "Color.h"
#include "Board.h"

class Numbers {
	int num = 0;
	int digits = 0;
	Point p;
	Color color = WHITE;
	bool isCorrect;
	bool checkAviablePoint(int x, int y, Board& board, int number);
	bool checkUpDown(int x, int y, Board& board);

public:
	bool isEqual(Numbers& other);
	void randNumber(Board& board);
	void drawNumber(Board & b);
	const Point& getNumPoint() const { return p; } //maybe return const by ref
	void setVal(int _num) { num = _num; }
	int getVal() { return num; }
	void setNumPoint(Point _p){ p.setPoint(_p); }
	void howManyDigits(int number);
	int getDigits() const { return digits; }
	void setColor(Color _color) { color = _color; }
	void eraseDigits(Board & b, int x, int y);
	void numSwap(Numbers & a);
	void eraseNumber(Board& board);
	void set_isCorrect(bool ans) { isCorrect = ans; }
	bool isNumCorrect() { return isCorrect; }
};

#endif