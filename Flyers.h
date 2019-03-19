#ifndef _FlYERS_H_
#define _FlYERS_H_

#include "Bullet.h"

class Flyers : public Bullet{
	bool screenCross; //indicates if the flyer crosses the screen
	bool isSensitive; // indicates if the flyer is bullet sensitive
	bool isDeleted; //indicates if the flyer has been shot
	bool doubleSpeed;
public:
	enum NumEaterPos { ROW = 10, COL = 19 };
	enum RowFlyerPos { RF1Row = 23, RF1Col = 30, RF2Row = 15, RF2Col = 50 };
	enum ColFlyerPos { CF1Row = 23, CF1Col = 45, CF2Row = 15, CF2Col = 55 };
	Flyers() {}
	Flyers( Direction dir, Point _p, Color _color, char _c, bool _isSensitive, bool _screenCross, bool _doubleSpeed, bool _isDeleted = false);
	bool isActive() { return !isDeleted; }
	void deleteFlyer() { isDeleted = true; }
	bool isFlyerSensitive() { return isSensitive; }
	bool isDoubleSpeed() { return doubleSpeed; }
	void revive() { isDeleted = false; }
	virtual void move();
	virtual void reset() {}

};


#endif
