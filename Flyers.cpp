#include "Flyers.h"

Flyers::Flyers(Direction dir, Point _p, Color _color, char _c, bool _isSensitive, bool _screenCross, bool _doubleSpeed, bool _isDeleted)
	: Bullet(_p, _color, _c)
{
	setDir(dir);
	screenCross = _screenCross;
	isSensitive = _isSensitive;
	isDeleted = _isDeleted;
	doubleSpeed = _doubleSpeed;
}

void Flyers::move()
{
	Point p;
	this->getPoint(p);
	if (screenCross == true)
		p.moveImpl();
	else
		p.moveButDontCross();

	this->setPoint(p); //update point
}

