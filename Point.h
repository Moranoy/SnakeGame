#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "Direction.h"
#include "Definitions.h"
#include "io_utils.h"
using namespace std;

class Point
{
	enum GameBorders { Top = MENU_ROWS, MaxLeft = 0, MaxRight = SCREEN_COLS - 1, Bot = SCREEN_ROWS - 1 };

	int x, y;
	int dir_x = 1;
	int dir_y = 0;
public:
	void moveImpl();
	void moveButDontCross();
	Point(int x1 = 1, int y1 = 1) : x(x1), y(y1) {}
	void getXY (int& _x, int& _y) const { _x = x; _y = y; }
	int getX() const { return x; }
	int getY() const { return y; }
	void setXY(int _x, int _y){ x = _x; y = _y; }
	bool isEqual(const Point& p);
	void getDir(int& dirX, int& dirY) { dirX = dir_x; dirY = dir_y; }
	void setDir(int dirX, int dirY) { dir_x = dirX; dir_y = dirY; }
	void changeDir(Direction dir); //over loading
	void changeDir(int index, char keyPressed);
	void move(Direction dir)
	{
		changeDir(dir);
		moveImpl();
	}
	void setPoint(Point& pt)
	{
		x = pt.getX();
		y = pt.getY();
		pt.getDir(dir_x, dir_y);
	}

};

#endif
