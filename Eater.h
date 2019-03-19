#ifndef _EATER_H_
#define _EATER_H_

#include "Flyers.h"
#include <list>
#include "Numbers.h"


class Eater : public Flyers {
	bool inPersuit;
	Numbers target;
	int currDistance;
	Direction rowDir;
	Direction colDir;
	//enum NumEaterPos { ROW = 10, COL = 19 };
public:
	Eater(Point p, bool _inPersuit = false)
		: inPersuit(_inPersuit), Flyers(Direction::RIGHT, p, Color::LIGHTGREEN, NUM_EATER_CHAR, true, true, false)
		{}
	void setCurrDistance(int dist) { currDistance = dist; } 
	bool isDistShorter(const Numbers& num);
	int dist(const Numbers& num);
	int getShortestPath(int eaterPos, int numPos, bool isRow, int digits = 0);
	int getDirectColPath(int eaterX, int numX, int digits);
	int getCrossColPath(int eaterX, int numX, int digits);
	virtual void move () override;
	void updateIsCorrectTarget();
	void setDir(int x, int y, int digits);
	void setRowDir(int numY, int eaterY);
	void setColDir(int x, int y, int digits);
	void changeEaterDir(Point & eaterPoint);
	void endPersuit() { inPersuit = false; }
	void setTarget(Numbers& num);
	void setTarget(int num, const Point& p, int digits);
	const Numbers getTarget(){ return target; }
	bool isInPersuit() {return inPersuit; }
	virtual void reset() override;
};
#endif