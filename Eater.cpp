#include "Eater.h"


bool Eater::isDistShorter(const Numbers& num)
{
	Point numPoint, eaterPoint;
	numPoint = num.getNumPoint();
	getPoint(eaterPoint);

	if (dist(num) < dist(target)) //distance from num is shorter than distance from current target
		return true;
	else
		return false;
}

int Eater::dist(const Numbers& num)
{
	Point numPoint, eaterPoint;
	getPoint(eaterPoint);
	int numX, numY, eaterX, eaterY;
	int colPathLen, rowPathLen, pathLen;

	numPoint = num.getNumPoint();
	numPoint.getXY(numX, numY);
	eaterPoint.getXY(eaterX, eaterY);
	colPathLen = getShortestPath(eaterX, numX, false, num.getDigits());
	rowPathLen = getShortestPath(eaterY, numY, true);

	pathLen = colPathLen + rowPathLen;
	return pathLen;
}


int Eater::getShortestPath(int eaterPos, int numPos, bool isRow, int digits) //return the shortest path between 2 X'es or Y'es
{
	int shortestPath, directPath, borderCrossPath;
	if (isRow)
	{
		directPath = abs(eaterPos - numPos);
		borderCrossPath = SCREEN_COLS - abs(eaterPos - numPos);
	}
	else	//deal with cols differently because of the numbers multiple digits
	{
		directPath = getDirectColPath(eaterPos, numPos, digits);
		borderCrossPath = getCrossColPath(eaterPos, numPos, digits);
	}


	if (directPath <= borderCrossPath)
		shortestPath = directPath;
	else
		shortestPath = borderCrossPath;

	return shortestPath;
}

int Eater::getDirectColPath(int eaterX, int numX, int digits)
{
	if (eaterX > numX)
		return eaterX - (numX + digits - 1);
	else if (eaterX < numX)
		return numX - eaterX;
	else
		return 0;
}

int Eater::getCrossColPath(int eaterX, int numX, int digits)
{
	if (eaterX > numX + digits - 1)
		return SCREEN_COLS - (eaterX - numX);
	else if (eaterX < numX)
		return SCREEN_COLS - (numX + digits - 1 - eaterX);
	else
		return 0;
}

void Eater::move()
{
	if (inPersuit)
	{
		Point eaterPoint;

		getPoint(eaterPoint);
		changeEaterDir(eaterPoint);
		eaterPoint.moveImpl();
		setPoint(eaterPoint);
	}
}
void Eater::setTarget(int num, const Point& p, int digits)
{
	int x, y;
	target.setVal(num);
	target.setNumPoint(p);
	p.getXY(x, y);
	inPersuit = true;
	setDir(x, y, digits);
}
void Eater::reset()
{
	//Point p;
	//this->getPoint(p);
	//gotoxy(p.getX(), p.getY());
	////cout << EMPTY_CHAR;
	//this->endPersuit();
	//p.setXY(ROW, COL);
	//this->setPoint(p);
	//revive();		 //incase eater has been shot
}
void Eater::setTarget(Numbers& num)
{
	Point p;
	setTarget(num.getVal(), num.getNumPoint(), num.getDigits());
	this->getPoint(p);
	setCurrDistance(dist(num));
}

void Eater::updateIsCorrectTarget()
{
	target.set_isCorrect(false);
}
void Eater::setDir(int numX, int numY, int digits)
{
	Point eaterPoint;
	int eaterX, eaterY;

	getPoint(eaterPoint);
	eaterPoint.getXY(eaterX, eaterY);
	setRowDir(numX, eaterY);
	setColDir(numX, eaterX, digits);
	Bullet::setDir(rowDir);
}

void Eater::setRowDir(int numY, int eaterY)
{
	int directPath, crossPath;

	directPath = abs(eaterY - numY);
	crossPath = SCREEN_COLS - abs(eaterY - numY);

	if (directPath < crossPath && eaterY > numY) //direct path is shorter and eater is bellow number
		rowDir = UP;
	else if (directPath > crossPath && eaterY < numY) //cross path is shorter and eater is above number
		rowDir = UP;
	else
		rowDir = DOWN;
}

void Eater::setColDir(int numX, int eaterX, int digits)
{
	int directPath, crossPath;

	directPath = getDirectColPath(eaterX, numX, digits);
	crossPath = getCrossColPath(eaterX, numX, digits);

	if (directPath < crossPath && eaterX < numX) //direct path is shorter, and eater is to the left of the number
		colDir = RIGHT;
	else if (crossPath < directPath && numX < eaterX) //cross path is shorter, and eater is to the right of the number
		colDir = RIGHT;
	else
		colDir = LEFT;
}
void Eater::changeEaterDir(Point& eaterPoint) //changes the direction of the eater
{
	Point numPoint;
	int eaterX, eaterY, targetX, targetY;

	numPoint = target.getNumPoint();

	eaterPoint.getXY(eaterX, eaterY);
	numPoint.getXY(targetX, targetY);

	int colPathLen, rowPathLen;
	int deltaX, deltaY;
	colPathLen = getShortestPath(eaterX, targetX, false, this->target.getDigits());
	rowPathLen = getShortestPath(eaterY, targetY, true);

	deltaX = abs(targetX - eaterX);
	deltaY = abs(targetY - eaterY);

	Direction newDirection;
	if (deltaX >= deltaY) // move by shortest way
	{
		if (targetX > eaterX)// move right
			newDirection = Direction::RIGHT;
		else // move left
			newDirection = Direction::LEFT;

		if (colPathLen < deltaX)// move around left/right border
		{
			if (newDirection == Direction::LEFT)
				newDirection = Direction::RIGHT;
			else if (newDirection == Direction::RIGHT)
				newDirection = Direction::LEFT;
		}
	}
	else
	{
		if (targetY > eaterY)// move down
			newDirection = Direction::DOWN;
		else // move up
			newDirection = Direction::UP;
		if (rowPathLen < deltaY)// move around top/bottom border
		{
			if (newDirection == Direction::UP)
				newDirection = Direction::DOWN;
			else if (newDirection == Direction::DOWN)
				newDirection = Direction::UP;
		}
	}

	eaterPoint.changeDir(newDirection);
	setPoint(eaterPoint);

}
