#ifndef _SHOT_H_
#define _SHOT_H_

#include "Bullet.h"

class Shot : public Bullet {
	int shooter_snake_index = 0;
public:
	Shot() {}

	int getShooterIndex() { return shooter_snake_index; }
	void static swapShots(Shot& s1, Shot& s2);
	void setShooterIndex(int index) { shooter_snake_index = index; }
};

#endif