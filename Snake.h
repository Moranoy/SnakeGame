#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "Direction.h"
#include "Board.h"
#include "Color.h"
#include <Windows.h>
#include "Shot.h"

class Snake {
	Point body[MAX_BODY_SIZE];
	Color color;
	Direction direction;
	size_t size = INIT_SIZE;
	size_t shotsAvailable;
	size_t currShotsOnBoard;
	Shot shotsArr[MAX_SHOT_ARR_SIZE];
	char shootKey;
	char c;
	char dirKeys[DIR_KEYS]; // the keys for the four possible directions
	bool isPaused;
	size_t unPauseTurn;
public:
	Snake() {}
	Snake(const Point& head, char c1, Color color, Direction dir, size_t _unPauseTurn = 0, bool pause_flag = false, size_t _shotsAvailable = INIT_SHOTS, size_t _currShotsOnBoard = 0);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown, char shootKey);
	void changeDir(char keyPressed);
	bool isValidDir(Direction newDir);
	void move(char keyPressed, char nextMove, Board& board);
	void getSnakeHead(Point& sHead) { sHead = body[0]; }
	int getSize() { return size; }
	Point* getBody() { return body; }
	char getShape() { return c; }
	void increaseBodySize();
	void printSnakeOnBoard(Board& b, int& rowInd, int& colInd);
	void drawYourself(Board& b);
	void relocateSnake(int x, int y, Direction dir, Board& b);
	void eraseSnake(Board& b);
	int getBodySize() { return size; }
	void setColor(Color c) { color = c; }
	Color getColor() { return color; }
	int getHowManyShotsAviable() { return shotsAvailable; }
	int getHowManyShotsOnBorad() { return currShotsOnBoard; }
	void setHowManyShotsOnBorad(int _currShotsOnBoard) { currShotsOnBoard = _currShotsOnBoard; }
	Shot getShotFromArr(int index) { return shotsArr[index]; }
	void setShotInArr(Point& _point, int shotIndex, int snakeIndex);
	bool didTheSnakeGotHit(Point & p);
	void pauseSnake(int currTurn);
	bool isSnakePaused();
	void findAndDeleteShotFromArr(const Point& p);
	void deleteShotFromArr(int index, Point& p);
	bool isShotInArray(const Point & p);
	void deleteAllShots(Board& b);
	void unPauseSnake() { isPaused = false; }
	void setHowManyShotsAviable(int _shotsAvailable) { shotsAvailable = _shotsAvailable; }
	void updateShotsCounter(bool reduce);
	int isShotFired(char keyPressed);
	bool timeToUnPause(size_t currTurn);
	void deleteShotFromArrByIndex(int index);
	void compressShotsInArr();
};
#endif
