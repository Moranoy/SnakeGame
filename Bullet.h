#ifndef _BULLET_H_
#define _BULLET_H_

#include "Point.h"
#include "Board.h"
#include "Color.h"


class Bullet {
	Point point;
	char c = SHOT_CHAR;
	Color color = BROWN;
public:
	Bullet(Point _p, Color _color, char _c = SHOT_CHAR);
	Bullet() {}
	void getPoint(Point& p) { p = point; }
	void setPoint(Point& p) { point.setPoint(p); }
	Color getColor() { return color; } 
	void setColor(Color _color) { color = _color; }
	void setDir(Direction dir) { point.changeDir(dir); }
	char getSign() { return c; }
};


#endif