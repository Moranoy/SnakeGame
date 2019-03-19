#include "Point.h"

void Point::moveImpl() 
{
	if (y == Top && dir_y == -1)
		y = Bot;
	else if (y == Bot && dir_y == 1)
		y = Top;
	else if (x == MaxRight && dir_x == 1)
		x = MaxLeft;
	else if (x == MaxLeft && dir_x == -1)
		x = MaxRight;
	else
	{
		x = x + dir_x;
		y = y + dir_y;
	}
}

void Point::moveButDontCross()
{
	if (y == Top && dir_y == -1)	//reverse the direction of the point so that when it reaches the borders of the game it
		dir_y = 1;									//will circle backwards
	else if (y == Bot && dir_y == 1)
		dir_y = -1;
	else if (x == MaxRight && dir_x == 1)
		dir_x = -1;
	else if (x == MaxLeft && dir_x == -1)
		dir_x = 1;
	
	x = x + dir_x;	//advance point
	y = y + dir_y;
	
}

void Point::changeDir(Direction dir) 
{
	switch (dir) 
	{
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}

void Point::changeDir(int index, char keyPressed)
{
	if (index == 0)
	{
		if (keyPressed == 'w') //up
		{
			dir_x = 0;
			dir_y = -1;
		}
		else if (keyPressed == 'x')//down
		{
			dir_x = 0;
			dir_y = 1;
		}
		else if (keyPressed == 'a') //left
		{
			dir_x = -1;
			dir_y = 0;
		}
		else if (keyPressed == 'd') //right
		{
			dir_x = 1;
			dir_y = 0;
		}
	}
	else
	{
		if (keyPressed == 'i') //up
		{
			dir_x = 0;
			dir_y = -1;
		}
		else if (keyPressed == 'm') //down
		{
			dir_x = 0;
			dir_y = 1;
		}
		else if (keyPressed == 'j') //left
		{
			dir_x = -1;
			dir_y = 0;
		} 
		else if (keyPressed == 'l') //right
		{
			dir_x = 1;
			dir_y = 0;
		}
	}
}

bool Point::isEqual(const Point& p)
{
	bool b = this->x == p.x && this->y == p.y;
	return b;
}

