#include "Shot.h"

void Shot::swapShots(Shot& s1, Shot& s2)
{
	int shooterIndexTemp;
	Point p1, p2;
	s1.getPoint(p1);
	shooterIndexTemp = s1.getShooterIndex();

	s2.getPoint(p2);
	s1.setPoint(p2);
	s1.setShooterIndex(s1.getShooterIndex());

	s2.setPoint(p1);
	s2.setShooterIndex(shooterIndexTemp);
}

