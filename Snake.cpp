#include "Snake.h"


Snake::Snake(const Point& head, char apearance, Color _color, Direction dir, size_t _unPauseTurn, bool pause_flag, size_t _shotsAvailable, size_t _currShotsOnBoard)
{
	c = apearance;
	color = _color;
	currShotsOnBoard = _currShotsOnBoard;
	shotsAvailable = _shotsAvailable;
	unPauseTurn = _unPauseTurn;
	isPaused = pause_flag;

	Point bodyTemp[INIT_SIZE];
	bodyTemp[0] = head;

	if (c == SNAKE_1_CHAR)
		direction = Direction::RIGHT;
	else
		direction = Direction::LEFT;

	for (int i = 1; i < INIT_SIZE; ++i) 
	{
		bodyTemp[i] = bodyTemp[i - 1];
		bodyTemp[i].move(direction);    
	}
	// head in the first location
	for (int i = 0; i < INIT_SIZE; i++)
	{
		body[i].setPoint(bodyTemp[INIT_SIZE - i - 1]);
		body[i].changeDir(dir);
	}
	
}
void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown, char _shootKey) 
{
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
	shootKey = _shootKey;
}
void Snake::changeDir(char keyPressed) 
{
	for (const auto& key : dirKeys) 
		if (key == keyPressed)
		{
			Direction newDir = (Direction)(&key - dirKeys);
			
			if (isValidDir(newDir) == true)
			{ 
				direction = newDir;
				body[0].changeDir(direction);
			}
			return;
		}
}

bool Snake::isValidDir(Direction newDir)
{
	if (newDir == UP && direction == DOWN)
		return false;
	if (newDir == DOWN && direction == UP)
		return false;
	if (newDir == RIGHT && direction == LEFT)
		return false;
	if (newDir == LEFT && direction == RIGHT)
		return false;
	else
		return true;
}
void Snake::move(char keyPressed, char nextMove, Board& b)
{
	int x, y, _x, _y;
	Direction lastDir = direction;
	_x = body[size - 1].getX();
	_y = body[size - 1].getY();
	setTextColor(color);

	changeDir(keyPressed);
	if (nextMove != IS_SNAKE) 
	{
		for (int i = this->size - 1; i > 0; --i)
		{
			body[i].setPoint(body[i - 1]);
			x = body[i].getX();
			y = body[i].getY();
			setTextColor(color);
			b.setAndDrawPoint(x, y, this->c); 
		}
		setTextColor(color);
		b.setAndDrawPoint(_x, _y, EMPTY_CHAR); //erase snakes tail
		
		changeDir(keyPressed);
		body[0].move(direction); //point move
		x = body[0].getX();
		y = body[0].getY();
		setTextColor(color);
		b.setAndDrawPoint(x, y, this->c);
	}

}

void Snake::printSnakeOnBoard(Board& b, int& rowInd, int& colInd)
{
	int x, y, sSize;
	char c;
	Point* sBody;

	c = getShape();
	sSize = size;
	sBody = body;

	sBody[sSize - 1].getXY(colInd, rowInd);
	for (int i = 0; i < sSize; i++) //get all of the snakes private data members
	{
		sBody[i].getXY(x, y);
		setTextColor(color);
		b.setAndDrawPoint(x, y, c);
	}
}

void Snake::increaseBodySize() //return bool to indicate if a player has 15 points
{
	if (size < MAX_BODY_SIZE)
		size++;
}

void Snake::drawYourself(Board& b)
{
	for (size_t i = 0; i < size; i++)
		b.setAndDrawPoint(body[i].getX(), body[i].getY(), c);
}

void Snake::relocateSnake(int tailX, int tailY, Direction dir, Board& b)
{
	Point* bodyTemp = new Point[size];

	eraseSnake(b);
	direction = dir;
	
	bodyTemp[0].setXY(tailX, tailY);
	bodyTemp[0].changeDir(direction);

	for (size_t i = 1; i < size; ++i) 
	{
		bodyTemp[i] = bodyTemp[i - 1];
		bodyTemp[i].move(direction);
	}
	// head in the first location
	for (size_t i = 0; i < size; i++)
		body[i].setPoint(bodyTemp[size - i - 1]);

	delete[]bodyTemp;

	this->unPauseSnake();
}

void Snake::eraseSnake(Board& b)
{
	int x, y;
	for (size_t i = 0; i < size; i++)
	{
		body[i].getXY(x, y);
		b.setAndDrawPoint(x, y, EMPTY_CHAR);
	}
}

void Snake::updateShotsCounter(bool reduce)
{
	if (reduce && (shotsAvailable > 0))
		shotsAvailable--;
	else if (!reduce && (shotsAvailable < MAX_SHOT_ARR_SIZE))
		shotsAvailable++;
}

//checks if a shot has been fired, and returns the shooting snakes index (or NO_SNAKE_FIRED)
int Snake::isShotFired(char keyPressed)
{
	if (this->c == SNAKE_1_CHAR && keyPressed == SNAKE_1_SHOT)
		return 0;
	else if (this->c == SNAKE_2_CHAR && keyPressed == SNAKE_2_SHOT)
		return 1;
	else
		return NO_SNAKE_FIRED;	
}

void Snake::setShotInArr(Point& _point, int shotIndex, int snakeIndex)
{
	shotsArr[shotIndex].setShooterIndex(snakeIndex);
	shotsArr[shotIndex].setPoint(_point);
}

bool Snake::didTheSnakeGotHit(Point& p)
{
	Point* temp;
	int size = getBodySize();
	temp = getBody();
	for (int j = 0; j < size; j++)
		if (temp[j].isEqual(p)) //if the shot point is equal to snake's body point
			return true;

	return false;
}

void Snake::pauseSnake(int currTurn)
{
	isPaused = true;
	unPauseTurn = currTurn + TIME2WAIT;
}

bool Snake::isSnakePaused()
{
	bool res;
	if (isPaused == false)
		res = false;
	else 
		res = true;

	return res;
}

void Snake::findAndDeleteShotFromArr(const Point& p)
{//deletes all the shots that have the same point as the function's input
	Point temp;
	for (size_t i = 0; i < currShotsOnBoard; i++)
	{
		shotsArr[i].getPoint(temp);
		if (temp.isEqual(p))
			deleteShotFromArr(i, temp);
	}
}
void Snake::deleteShotFromArr(int index, Point& p)
{
	int i, index2 = currShotsOnBoard - 1;

	p.setXY(DUMMY_INT, DUMMY_INT); //initialize the shot
	shotsArr[index].setPoint(p);
	shotsArr[index].setShooterIndex(0);

	if (currShotsOnBoard > 1) //in case of more the one shot on board (of the same player) we will do swap
	{
		// remove shot by index and compress all shots
		for (i = 0; i < index - 1; i++)
			shotsArr[i].swapShots(shotsArr[i], shotsArr[i + 1]);
		for (i = index; i < (int)currShotsOnBoard - 1; i++)
			shotsArr[i].swapShots(shotsArr[i], shotsArr[i + 1]);
	}
	currShotsOnBoard--;
}

bool Snake::isShotInArray(const Point& p)
{//deletes all the shots that have the same point as the function's input
	Point temp;
	for (size_t i = 0; i < currShotsOnBoard; i++)
	{
		shotsArr[i].getPoint(temp);
		if (temp.isEqual(p))
			return true;
	}
	
	return false;
}
void Snake::deleteAllShots(Board& b)
{
	int i, x, y, numOfShots = this->getHowManyShotsOnBorad();
	Point shot, p;
	p.setXY(DUMMY_INT, DUMMY_INT);
	for (i = 0; i < numOfShots; i++)
	{
		shotsArr[i].getPoint(shot);
		shot.getXY(x, y);
		b.setAndDrawPoint(x, y, EMPTY_CHAR);
		shotsArr[i].setPoint(p);
	}
	this->setHowManyShotsOnBorad(0);
}

bool Snake::timeToUnPause(size_t currTurn)
{
	bool res;
	if (isPaused == true && currTurn >= unPauseTurn)
		res = true;
	else
		res = false;

	return res;
}
void Snake::deleteShotFromArrByIndex(int index)
{
	Point p;
	p.setXY(DUMMY_INT , DUMMY_INT); //initialize the shot
	shotsArr[index].setPoint(p);
	shotsArr[index].setShooterIndex(DUMMY_INT);
}
void Snake::compressShotsInArr()
{
	int freeIndex = -1;
	int currShotsOnBoardNew = currShotsOnBoard;
	for (int i = 0; i < (int)currShotsOnBoard; i++)
	{
		if (shotsArr[i].getShooterIndex() == DUMMY_INT)
			currShotsOnBoardNew--;
		if (freeIndex == DUMMY_INT && shotsArr[i].getShooterIndex() == DUMMY_INT)
			freeIndex = i;
		else
		{
			if (freeIndex >= 0)
			{
				shotsArr[i].swapShots(shotsArr[freeIndex], shotsArr[i]);
				freeIndex = i;
			}
		}
	}
	currShotsOnBoard = currShotsOnBoardNew;
}