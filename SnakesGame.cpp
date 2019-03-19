#include "SnakesGame.h"
#include <iostream>
#include <string>
#include <typeinfo>

void SnakesGame::initScreen() 
{ 
	board.resetBoard();

	for (int i = 0; i < MENU_ROWS; i++)//init menu screen 
		for (int j = 0; j < SCREEN_COLS; j++)
			screenMenu[i][j] = EMPTY_CHAR;
}

void SnakesGame::resetGame(bool& startGame)
{
	startGame = false;
	if (replay.isReplay())
	{
		replay.getStartingNumbers(numArr, numArrSize);
		startGame = true;
	}
	menu.displayMenuScreen(startGame, false, false, EMPTY_CHAR, screenMenu, numArr); //display both screens
	updateNumList();
	resetGameObjects(true, true, true, false, !replay.isReplay()); //reset objects on screen
	for (int i = 0; i < SNAKES_ARR_SIZE && !replay.isReplay(); i++) //reset snakes		
			s[i] = sOriginal[i];
	
	if (!replay.isReplay())
	{
		replay.reset(s);
		deleteNumbers(false); //reset numbers array
	}
	
	board.resetBoard();//reset board
	board.drawYourself();
	drawNumbers(); 
	menu.deleteAllGameMenus(false);
	currTurn = 0;
}

void SnakesGame::drawNumbers() //draw numbers array
{
	for (int i = 0; i < numArrSize; i++)
		numArr[i].drawNumber(board);
}

//the main function of SnakesGame, operates the entire game
void SnakesGame::run()
{
	bool startGame = false, instructions = false, deleteTail_flag = false, exit_flag = false, moveCols, endMission=false;

	if(!replay.isReplay())
		menu.loadMissionBank();	//load missions if not in a replay

	resetGame(startGame);

	while (!exit_flag)
	{
		if ((_kbhit() || replay.isReplay()) && snakesAreMoving)
		{
			exit_flag = keyHit(instructions, startGame);
			if (exit_flag == true)
				break;
		}
		Sleep(70);
		if (!startGame)
			continue;
		
		endMission = moveAllBullets(moveCols);
		if (endMission)
		{
			executeGameMenu(5, startGame);
			continue;
		}
		if (snakesAreMoving)
		{
			if (currTurn % TIME2SPAWN == 0 && currTurn != 0) //every 5 steps rand number
				spawnNumber();
			currTurn++;

			endMission = moveAllSnakes(exit_flag);
			if (endMission)
			{
				executeGameMenu(5, startGame);
				continue;
			}
			if (numArrSize == MAX_NUM_ARR_SIZE) //max numbers on board
			{
				sparklingNumbers(menu.getMissionInd());
				deleteNumbers(true);
				startingPosition();
				replay.reset(s);
			}
		}
		snakesAreMoving = !snakesAreMoving; 
	}//while
}

bool SnakesGame::moveAllBullets(bool& moveCols)
{
	bool endMission=false;
	moveAllShots();
	if (moveFlyers(moveCols))
		endMission = true;
	moveCols = !moveCols; //toggle the bool
	return endMission;
}

bool SnakesGame::keyHit(bool& instructions, bool& startGame)
{
	bool exit_flag;
	keyPressed = getInput();
	if (!startGame)
	{
		if (keyPressed == Menu::MenuOptions::_ExitGame)
			return true;
		else if (keyPressed == Menu::MenuOptions::_Instructions)
		{
			instructions = true;
			menu.displayMenuScreen(false, instructions, false, keyPressed, screenMenu, numArr);
		}
		else if (keyPressed == Menu::MenuOptions::_StartGame)
		{
			startGame = true;
			menu.displayMenuScreen(startGame, instructions, true, keyPressed, screenMenu, numArr);
			updateSnakesRow();
		}
	}
	else
	{
		if (keyPressed == KEYS::ESC)
		{
			menu.displayMenuScreen(startGame, instructions, false, keyPressed, screenMenu, numArr);
			while (true) //secondary menu
			{
				keyPressed = getInput();
				if (replay.isReplay() && keyPressed != Menu::SecondMenu::_Resume) //if we got here with the replay, end it
				{
					bool validInput = false;
					while (!validInput)
					{
						keyPressed = _getch(); //get char without saving the input 
						validInput = (keyPressed >= Menu::SecondMenu::_Exit && keyPressed <= Menu::SecondMenu::_Replay);
					}

					return true;
				}
				if (keyPressed >= Menu::SecondMenu::_Exit && keyPressed <= Menu::SecondMenu::_Replay) //is keyPressed valid
				{
					exit_flag = executeGameMenu(keyPressed - '0', startGame);
					if (keyPressed == Menu::SecondMenu::_Exit || exit_flag == true)
						return true; //exit the game
					else
						return false;
				}
			}
		}
	}
	return false;
}

char SnakesGame::getInput()
{
	if (replay.isReplay())
		return replay.getInput(currTurn);
	else
	{
		char c = _getch();

		//if (c == Menu::SecondMenu::_Replay)
		//	replay.setInput(Menu::SecondMenu::_Resume, currTurn); //save replay key as resume
		//else
			replay.setInput(c, currTurn);
		return c;
	}
}
void SnakesGame::spawnNumber()
{
	Numbers n;
	bool _isCorrect;

	if (replay.isReplay())
	{
		n = replay.getNumber();
		n.drawNumber(board);
	}
	else
	{
		n.randNumber(board);
		replay.addNumber(n);
	}
	set_isCorrect(n);
	numArr[numArrSize] = n;

	_isCorrect = numArr[numArrSize].isNumCorrect();
	if (_isCorrect) //insert to list
	{
		numList.push_back(&numArr[numArrSize]);
		if (numEater.isInPersuit()) //if the num eater in a persuit
		{
			if (numEater.isDistShorter(n)) //new target
				numEater.setTarget(n);
		}
		else
			numEater.setTarget(n); //if the number is correct and its the new eater's target
	}
	numArrSize++;
}
void SnakesGame::set_isCorrect(Numbers& number)
{
	if (menu.isNumberCorrect(number.getVal(), numArr, numArrSize))
		number.set_isCorrect(true);
	else
		number.set_isCorrect(false);
}


char SnakesGame::availableNextMove(int index)
{
	Point sHead, temp;
	int  x, y;
	char isAvailable;
	
	s[index].getSnakeHead(sHead);
	temp = sHead;
	temp.getXY(x, y);
	temp.changeDir(index, keyPressed);
	temp.moveImpl();
	temp.getXY(x, y); //update x,y by new point

	isAvailable = checkNextMove(x, y);
	if (isAvailable == IS_SNAKE)
	{
		temp = sHead;
		temp.moveImpl();
		temp.getXY(x, y);
		isAvailable = checkNextMove(x, y);
	}
	return isAvailable;
}
char SnakesGame::checkNextMove(int x, int y)
{
	char c = board.screenGame[y][x];
	if (isNum(c) == true) //next move is a number
		return IS_NUMBER;
	switch (c)
	{
	case SNAKE_1_CHAR:
		return IS_SNAKE;
		break;
	case SNAKE_2_CHAR: //next move is a snake
		return IS_SNAKE;
		break;
	case SHOT_CHAR: //next move is a shot
		return IS_SHOT;
		break;
	case COL_FLYER_CHAR: //next move is a col flyer
		return IS_COL_FLYER;
		break;
	case ROW_FLYER_CHAR: //next move is a row flyer
		return IS_ROW_FLYER;
		break;
	case NUM_EATER_CHAR: //next move is the num eater
		return IS_NUM_EATER;
		break;
	default:
		return EMPTY_CHAR; //next move is empty
		break;
	}
}
void SnakesGame::eatNum(int sIndex)
{
	int  num, numIndex, howManyShotsAviable, questionInd;
	Point sHead, nextPoint, startOfNumPoint;

	//functions that get the next point -need x,y and dir
	s[sIndex].getSnakeHead(sHead);
	nextPoint = sHead;
	nextPoint.moveImpl();

	num = deleteNum(numIndex, nextPoint, startOfNumPoint); //remove number from array, screen, and return value
	questionInd = menu.getMissionInd(); //get the question index
	howManyShotsAviable = s[sIndex].getHowManyShotsAviable();
	if (menu.isNumberCorrect(num, numArr, numArrSize) == true)
	{
		s[sIndex].increaseBodySize(); //increase the snake's body size
		menu.printCorrectAnswer(true, s[sIndex].getShape(), false);
		menu.updateSnakesMessageRow(sIndex, s[sIndex].getBodySize(), howManyShotsAviable);//update size on row 3
		Sleep(SLEEP_TIME_SHORT);
	}
	else
	{
		if (sIndex == 1)
		{
			s[0].increaseBodySize(); //increase the other snake's body size
			menu.printCorrectAnswer(false, s[sIndex].getShape(), false);
		}
		else
		{
			s[1].increaseBodySize();
			menu.printCorrectAnswer(false, s[sIndex].getShape(), false);
		}
	}

	sparklingNumbers(questionInd);	
	resetGameObjects(true, true, true, false, false);
	deleteNumbers(true);

	menu.displayMenuScreen(true, false, true, EMPTY_CHAR, screenMenu, numArr); //choose new question and update menu screen
	updateSnakesRow();
	replay.reset(s); //reset all numbers/input/snakes for new mission
	replay.saveNumbersOnScreen(numArr, numArrSize); //save all of the numbers that remained 
	
}


int SnakesGame::deleteNum(int& numIndex, Point& nextPoint, Point& startOfNumPoint)
{
	int val;
	bool updatelist = false;
	getStartOfNumPoint(nextPoint, startOfNumPoint);
	numIndex = getHitNumIndex(startOfNumPoint); //find the hitNum in the num array

	val = numArr[numIndex].getVal();
	numArr[numIndex].numSwap(numArr[numArrSize - 1]); //switch position in arr
	
	Point pt = numArr[numArrSize - 1].getNumPoint();
	if (numArr[numArrSize - 1].isNumCorrect())//if point exist in numList - remove it and add same point from new location
	{
		findAndRemoveFromNumListHelper(pt);
		updatelist = true;
	}
	else if(numArr[numIndex].isNumCorrect())
		updatelist = true;

	numArr[numArrSize - 1].eraseNumber(board);
	numArrSize--;
	if (updatelist)
		updateNumList();

	return val;
}

void SnakesGame::getStartOfNumPoint(Point& nextPoint, Point& numPoint)
{
	int x, y;
	nextPoint.getXY(x, y);

	while (board.screenGame[y][x] != EMPTY_CHAR && board.screenGame[y][x] != SNAKE_1_CHAR && board.screenGame[y][x] != SNAKE_2_CHAR)
		x--;
	
	numPoint.setXY(x+1, y);
}

int SnakesGame::getHitNumIndex(Point& nextP) //deal with number after its been erased
{
	int i;
	Point currNumPoint;

	for (i = 0; i < numArrSize; i++)
	{
		currNumPoint = numArr[i].getNumPoint();
		if (nextP.isEqual(currNumPoint)) 
			return i;
	}
	return 0;
}


bool SnakesGame::isNum(char c)
{
	if (c <= '9' && c >= '0')
		return true;
	
	return false;
}

void SnakesGame::sparklingNumbers(int questionInd)
{
	for (int i = 0; i < SPARKLE_TIMES; i++)
	{
		changeNumsColor(BLUE, questionInd);
		Sleep(SLEEP_TIME / SPARKLE_TIMES);
		changeNumsColor(LIGHTMAGENTA, questionInd);
		Sleep(SLEEP_TIME / SPARKLE_TIMES);
	}
	setTextColor(Color::WHITE);
	changeNumsColor(WHITE, questionInd);
}

void SnakesGame::changeNumsColor(Color color, int index)
{
	Point point;
	for (int i = 0; i < numArrSize; i++)
	{
		setTextColor(color);
		if (numArr[i].isNumCorrect())
		{ 
			numArr[i].setColor(color);
			point = numArr[i].getNumPoint();
			gotoxy(point.getX(), point.getY());
			cout << numArr[i].getVal();
		}
	}
}

void SnakesGame::deleteNumbers(bool deleteHalf)
{
	int newArrSize;

	if (deleteHalf) //delete half array
	{
		randomizeArray();
		newArrSize = numArrSize / 2;
	}
	else //delete all the array
	{
		replay.unsaveNumbers(); 
		newArrSize = 0;
	}
	for (int i = numArrSize - 1; i >= newArrSize; i--)
		numArr[i].eraseNumber(board);
	
	numArrSize = newArrSize;

	if (!numList.empty())
		numList.clear(); //reset List 
}

//go over the numArray and switch the numbers randomly so we can delete them randomly later on
void SnakesGame::randomizeArray()
{
	int randIndex, i;

	for (i = 0; i < numArrSize; i++)
	{
		randIndex = rand() % numArrSize;
		numArr[i].numSwap(numArr[randIndex]);
	}
}

//relocates the snakes at their starting positions
void SnakesGame::startingPosition()
{
	int s1Size, s2Size;
	for (int i = 0; i < SNAKES_ARR_SIZE; i++)
		s[i].eraseSnake(board);
	keyPressed = 0;
	s1Size = s[0].getSize();
	clearLocation(START_POSITION_COL1 , START_POSITION_ROW, Direction::RIGHT, s1Size);
	s[0].relocateSnake(START_POSITION_COL1, START_POSITION_ROW , Direction::RIGHT, board);

	s2Size = s[1].getSize();
	clearLocation(START_POSITION_COL2, START_POSITION_ROW, Direction::LEFT, s2Size);
	s[1].relocateSnake(START_POSITION_COL2, START_POSITION_ROW, Direction::LEFT, board);
}

int SnakesGame::runReplay(bool& replayGame)
{
	int index;

	index = keyPressed - '0';

	if (keyPressed >= Menu::SecondMenu::_Exit && keyPressed <= Menu::SecondMenu::_Replay)
	{
		if (index == Menu::SecondMenu::_Replay - '0')
		{
			replay.startReplay(s);
			numEater.endPersuit();
			run();
			return index;
		}
		else if (index == Menu::SecondMenu::_Resume - '0') //resume game - dont reset replay data members
			replay.endOfReplay();
		else
			replay.reset(s);

		replayGame = false;
	}
	return index;
}


bool SnakesGame::executeGameMenu(int index, bool& startGame)
{
	bool replayGame = index == Menu::SecondMenu::_Replay - '0'; //replay
	
	while(replayGame)	 //replay
		index = runReplay(replayGame);
	
	switch (index)
	{
	case 1: //exit program
		return true; 
		break;
	case 2: 
		resetGame(startGame);
		break;
	case 3:   //continue playing 
		updateGameMenu(false);
		break;
	case 4://restart same mission
		resetGameObjects(true, true, true, true, true);
		deleteNumbers(false);
		currTurn = 0;
		updateGameMenu(false);
		break;
	case 5: //start a new mission
		resetGameObjects(true, true, true, true, true); 
		updateGameMenu(true);
		updateNumList();
		replay.saveNumbersOnScreen(numArr, numArrSize);
		break;
	case 6:   //start new game 
		resetGame(startGame);
		startGame = true;
		menu.displayMenuScreen(startGame, false, true, Menu::MenuOptions::_StartGame, screenMenu, numArr);
		updateSnakesRow();
		break;
	default:
		break;
	}
	return false;
}

void SnakesGame::resetGameObjects(bool _resetShots, bool _resetFlyers, bool _resetPos, bool _resetNumOfShots, bool endReplay)
{
	if (_resetNumOfShots)
		resetHowManyShotsAviable();
	if (_resetShots)
		deleteAllShots();
	if (_resetFlyers)
		resetFlyers();
	if (_resetPos)
		startingPosition();
	if (endReplay)
		replay.reset(s);
	currTurn = 0;

	snakesAreMoving = true;
}

void SnakesGame::updateSnakesRow()
{
	for (int i = 0; i<SNAKES_ARR_SIZE; i++)
		menu.updateSnakesMessageRow(i, s[i].getBodySize(), s[i].getHowManyShotsAviable());//update snakes rows
}
void SnakesGame::updateGameMenu(bool newQuestion)
{
	menu.updateGameMenu(newQuestion);
	if (newQuestion)
		setNumArrAnswers();
	
	for (int i = 0; i < SNAKES_ARR_SIZE; i++)
		menu.updateSnakesMessageRow(i, s[i].getBodySize(), s[i].getHowManyShotsAviable());
}
void SnakesGame::moveAllShots()
{
	int howManyShots, x, y, numIndex, counterdeleteArr = 0;
	int deleteArr[MAX_SHOT_ARR_SIZE];
	char nextMove;
 	bool hasStop, hasDeleted=false;
	Shot shot, temp;
	Point nextShotPoint, currShotPoint, startOfNumPoint, flyerPoint;
	
	for (int i = 0; i < SNAKES_ARR_SIZE; i++) //run on snakes arr
	{
		howManyShots = s[i].getHowManyShotsOnBorad(); //get how many shots of each snake there are on board
		for (int j = 0; j < howManyShots; j++) //run on the shots arr
		{
			shot = s[i].getShotFromArr(j);
			shot.getPoint(nextShotPoint);
			nextShotPoint.getXY(x, y); //get current point index
			currShotPoint.setPoint(nextShotPoint); //save the curr potision
			board.setAndDrawPoint(x, y, EMPTY_CHAR);//delete current shot potision from board and screen
			nextShotPoint.moveImpl();
			nextShotPoint.getXY(x, y);//update x,y by new point
			nextMove = checkNextMove(x, y);

			switch (nextMove)
			{
			case IS_SNAKE:
				shotHitsSnake(i, nextShotPoint);
				hasStop = true;
				break;
			case IS_NUMBER:
				deleteNum(numIndex, nextShotPoint, startOfNumPoint); //delete number from screen and board
				hasStop = true;
				break;
			case IS_SHOT:
				for (int k = 0; k < SNAKES_ARR_SIZE; k++) //delete shots that got hit
				{
					board.setAndDrawPoint(x, y, EMPTY_CHAR);
					s[k].findAndDeleteShotFromArr(nextShotPoint); //delete the next shot
					s[k].findAndDeleteShotFromArr(currShotPoint); //delete the curr shot
					int sIndex = shot.getShooterIndex();
					if(sIndex != k)	//if there are different shooters, increase num of shots
						s[k].updateShotsCounter(false); 
					menu.updateSnakesMessageRow(k, s[k].getBodySize(), s[i].getHowManyShotsAviable());
				}
				hasDeleted = true;
				hasStop = true;
				break;
			case IS_COL_FLYER:
				for (int k = MAX_FLYERS_ARR_SIZE - 1; k > MAX_COL_FLYERS; k--) 
				{
					flyers[k]->getPoint(flyerPoint); //find hit flyer
					if(flyerPoint.isEqual(nextShotPoint))
						flyerHitsShot(k, flyerPoint, i); //delete col flyer
				}
				hasStop = true;
				break;
			case IS_ROW_FLYER:
				hasStop = true;
				break; 
			case IS_NUM_EATER:
				flyers[0]->getPoint(flyerPoint);
				flyerHitsShot(0, flyerPoint, i); //numEater dissapears 
				hasStop = true;
				break;
			case EMPTY_CHAR:
				hasStop = false;
				break;
			}

			if (!hasStop) //shot continue running
			{
				setTextColor(s[i].getColor());
				board.setAndDrawPoint(x, y, SHOT_CHAR);
				s[i].setShotInArr(nextShotPoint, j, i); //move shot's point
				setTextColor(Color::WHITE);
			}
			else
			{
				if (!hasDeleted) //shot has stopped and hasn't been deleted
				{
					board.setAndDrawPoint(x, y, EMPTY_CHAR); //delete shot from screen and board
					deleteArr[counterdeleteArr] = j; 
					counterdeleteArr++;
				}
			}				
		}
		if (counterdeleteArr > 0)
		{
			for (int k = 0; k < counterdeleteArr; k++)
				s[i].deleteShotFromArrByIndex(deleteArr[k]);
			s[i].compressShotsInArr();
			counterdeleteArr = 0;
		}
	}
}

bool SnakesGame::moveAllSnakes(bool& exit_flag)
{
	char nextMove_flag;
	int shootingSnakeInd, tailRowInd, tailColInd;
	Point sHead;

	for (size_t i = 0; i < SNAKES_ARR_SIZE; ++i)
	{
		if (s[i].timeToUnPause(currTurn) == true)
			SnakesGame::unPauseSnake(i); 
		if (s[i].isSnakePaused() == false)
		{
			s[i].printSnakeOnBoard(board, tailRowInd, tailColInd); 
			nextMove_flag = availableNextMove(i);

			if (nextMove_flag == IS_NUMBER)
			{
				eatNum(i);
				setNumArrAnswers();
			}
			else if (nextMove_flag == IS_COL_FLYER || nextMove_flag == IS_ROW_FLYER)
				snakeInPunshimet(i);
			else if (nextMove_flag == IS_NUM_EATER) 
			{
				numEaterHitsSnake(i); //end mission
				return true;
			}
			else if (nextMove_flag == IS_SHOT) //if snake steps on a shot
			{
				s[i].getSnakeHead(sHead);
				shotHitsSnake(i, sHead);
				for (int k = 0; k < SNAKES_ARR_SIZE; k++)
					s[k].findAndDeleteShotFromArr(sHead);
				snakeInPunshimet(i);
			}
			else
				s[i].move(keyPressed, nextMove_flag, board);
			shootingSnakeInd = s[i].isShotFired(keyPressed);
			if (shootingSnakeInd != NO_SNAKE_FIRED)
			{
				keyPressed = 0;
				createNewShot(shootingSnakeInd);
			}
			if (s[i].getBodySize() >= MAX_BODY_SIZE)
			{
				menu.printCorrectAnswer(true, s[i].getShape(), true);
				Sleep(SLEEP_TIME_SHORT);
				exit_flag = true;
			}
		}
	}
	return false;
}
void SnakesGame::setNumArrAnswers() 
{
	for (int i = 0; i < numArrSize; i++)
		set_isCorrect(numArr[i]);
}


//----------PAUSE SNAKE FUNCTIONS----------
void SnakesGame::unPauseSnake(int sIndex)
{
	int sSize = s[sIndex].getSize(), headX, headY, tailX, tailY;
	Direction newDir;

	s[sIndex].unPauseSnake(); //snake unPauseSnake
	if (!replay.isReplay()) //save relocation info
		setLegalLocation(headX, headY, newDir, sSize);
	else
		replay.getSnakeLocation(headX, headY, newDir, sSize); //get relocation info

	clearLocation(headX, headY, newDir, sSize);
	getTailLocation(tailX, tailY, headX, headY, newDir, sSize);
	s[sIndex].relocateSnake(tailX, tailY, newDir, board);
}

void SnakesGame::setLegalLocation(int& headX, int& headY, Direction& newDir, int sSize)
{
	bool isLegal_flag = false;

	while (isLegal_flag == false)
	{
		headX = (rand() % (SCREEN_COLS - sSize - 1)) + sSize; //so snake doesnt cross through the edges of the screen
		headY = (rand() % (GAME_ROWS - sSize - 1)) + sSize + MENU_ROWS - 2;
		newDir = Direction(rand() % DIR_ARR_SIZE);
		isLegal_flag = isLegalLocation(headX, headY, newDir, sSize); //check if location is legal
	}
	replay.setSnakeLocation(headX, headY, newDir, sSize);
}

//check if the chosen location is clear of snakes and shots
bool SnakesGame::isLegalLocation(int & headX, int & headY, Direction & newDir, int sSize)
{
	int toNextInd, i, currRow = headY, currCol = headX;
	bool moveRows;
	Point currPoint;

	if (isLegalLocationHelper(newDir)) //set the index's "direction", the way of checking the array
		toNextInd = -1;						//based on the newDir
	else
		toNextInd = 1;

	if (newDir == UP || newDir == DOWN)	//check if we go through the rows or the cols
		moveRows = true;
	else
		moveRows = false;

	for (i = 0; i < sSize; i++)
	{
		if (board.isInvalidLocation(currCol, currRow) == true) //if an invalid point is found, return false
			return false;
		if (moveRows == true)
			currRow += toNextInd;
		else
			currCol += toNextInd;
	}
	return true;
}

void SnakesGame::getTailLocation(int& tailX, int& tailY, int headX, int headY, int newDir, int sSize)
{
	if (newDir == UP)
	{
		tailX = headX;
		tailY = headY + sSize - 1;
	}
	else if (newDir == DOWN)
	{
		tailX = headX;
		tailY = headY - sSize + 1;
	}
	else if (newDir == RIGHT)
	{
		tailX = headX - sSize + 1;
		tailY = headY;
	}
	else 
	{
		tailX = headX + sSize - 1;
		tailY = headY;
	}
}

//pause and erase snake
void SnakesGame::snakeInPunshimet(int sIndex) 
{
	s[sIndex].eraseSnake(board);
	s[sIndex].pauseSnake(currTurn);
}
bool SnakesGame::isLegalLocationHelper(Direction & newDir)
{
	if (newDir == RIGHT || newDir == DOWN)
		return true;
	return false;
}

//clear the location from shots and numbers
void SnakesGame::clearLocation(int headCol, int headRow, Direction headDir, int sSize)
{
	int toNextInd, i, numIndex, currRow = headRow, currCol = headCol;
	bool moveRows;
	Point currPoint;

	if (isLegalLocationHelper(headDir)) //set the way we check the screen
		toNextInd = -1;
	else
		toNextInd = 1;

	if (headDir == UP || headDir == DOWN) //check if we go through rows or cols
		moveRows = true;
	else
		moveRows = false;

	for (i = 0; i < sSize; i++)
	{
		if (isNum(board.screenGame[currRow][currCol]))
		{
			currPoint.setXY(currCol, currRow);
			deleteNum(numIndex, currPoint, currPoint);
		}
		if (moveRows == true)
			currRow += toNextInd;
		else
			currCol += toNextInd;
	}
}


//----------SHOT FUNCTIONS----------
void SnakesGame::createNewShot(int sIndex) //in case keyPressed = IS_NUMBER or ='z'
{
	int  shotIndex, howManyShotsAviable;
	Point nextPoint;
	
	howManyShotsAviable = s[sIndex].getHowManyShotsAviable();
	if (howManyShotsAviable != 0)
	{
		shotIndex = s[sIndex].getHowManyShotsOnBorad();
		s[sIndex].updateShotsCounter(true); //reduce shots counter by 1
		s[sIndex].getSnakeHead(nextPoint);
		nextPoint.moveImpl();
		s[sIndex].setShotInArr(nextPoint, shotIndex, sIndex); //set shot in shots array
		board.setAndDrawPoint(nextPoint.getX(), nextPoint.getY(), SHOT_CHAR); //print shot on board
		s[sIndex].setHowManyShotsOnBorad(shotIndex + 1);
		menu.updateSnakesMessageRow(sIndex, s[sIndex].getBodySize(), s[sIndex].getHowManyShotsAviable());
	}
	else
		menu.printNoMoreShotsMessage(s[sIndex].getShape()); //print a message: no more Shots
}

int SnakesGame::whichSnakeGotHit(Point& point)
{
	bool firstSnake;
	int index = 0;

	firstSnake = s[index].didTheSnakeGotHit(point); //check if the snake got hit
	if (firstSnake)
		return index;
	else
		return index + 1;
}

void SnakesGame::shotHitsSnake(int i, Point& point)
{
	int hitSnakeIndex = whichSnakeGotHit(point); //get index of the snake that got hit by the shot
	if (i != hitSnakeIndex)
	{
		s[i].updateShotsCounter(false); //increase shooter shots counter
		menu.updateSnakesMessageRow(i, s[i].getBodySize(), s[i].getHowManyShotsAviable());
	}
	else
		s[i].updateShotsCounter(true);
	snakeInPunshimet(hitSnakeIndex);
}

void SnakesGame::deleteAllShots()
{
	for (int i = 0; i < SNAKES_ARR_SIZE; i++)
		s[i].deleteAllShots(board); //snakes deleteAllShots
}

void SnakesGame::resetHowManyShotsAviable()
{
	for (int i = 0; i < SNAKES_ARR_SIZE; i++)
		s[i].setHowManyShotsAviable(MAX_SHOT_ARR_SIZE);
}



//--------FLYER FUNCTIONS-----
bool SnakesGame::moveFlyers(bool moveDoubleSpeed) //move col flyers or only row flyers
{
	int i;
	for (i = 0; i < MAX_FLYERS_ARR_SIZE; i++)
		if (flyers[i]->isActive() == true && (flyers[i]->isDoubleSpeed() || (!flyers[i]->isDoubleSpeed() && !moveDoubleSpeed)))
		{
			if (moveCurrFlyer(i))	//if current flyer is still active, move it
				return true;
		}
	

	return false;
}

bool SnakesGame::moveCurrFlyer(int flyerIndex)
{
	int temp = 0, x, y;
	char nextMove_flag;
	Point p, tempPoint;
	bool isStillActive = true;
	int snakeIndex;
	
	flyers[flyerIndex]->getPoint(p);
	p.getXY(x, y);
	board.setAndDrawPoint(x, y, EMPTY_CHAR); //erase flyer
	flyers[flyerIndex]->move(); //move flyer
	flyers[flyerIndex]->getPoint(p); //get the current point (after moving)
	tempPoint = p;
	tempPoint.getXY(x, y);
	nextMove_flag = checkNextMove(x, y); //check the flyers next move

	if (nextMove_flag == IS_NUMBER)		//if a number is hit, delete number and keep going
	{
		temp = getHitNumIndex(tempPoint);
		deleteNum(temp, tempPoint, tempPoint);
	}

	else if (nextMove_flag == IS_SNAKE) //if a snake is hit, pause snake
	{
		snakeIndex = whichSnakeGotHit(p);
		if (flyerHitSnake(snakeIndex, flyerIndex))
			return true;
	}

	else if (nextMove_flag == IS_SHOT) //if a shot is hit
	{
		int i;
		bool shotFound;
		for (i = 0; i < SNAKES_ARR_SIZE; i++)
		{
			shotFound = s[i].isShotInArray(p);
			if (shotFound)
				snakeIndex = i;
		}
		isStillActive = flyerHitsShot(flyerIndex, p, snakeIndex);
		s[snakeIndex].findAndDeleteShotFromArr(p);
	}

	if (isStillActive)
	{
		p.getXY(x, y);
		setTextColor(flyers[flyerIndex]->getColor());
		board.setAndDrawPoint(x, y, flyers[flyerIndex]->getSign()); //draw flyer on screen
		setTextColor(Color::WHITE);
	}
	return false;
}



bool SnakesGame::flyerHitSnake(int snakeInd, int flyerIndex)
{
	if (flyerIndex == 0)
	{
		numEaterHitsSnake(snakeInd); //num eater
		return true;
	}
	else
	{
		snakeInPunshimet(snakeInd); //col/row flyer
		return false;
	}
}

bool SnakesGame::flyerHitsShot(int flyerIndex, const Point& p, int snakeIndex) //handles flyer and shot colision
{
	int x, y;
	bool isActive = true;

	if (flyers[flyerIndex]->isFlyerSensitive() == true) //flyer is sensitive to bullets, delete flyer
	{
		p.getXY(x, y);
		board.setAndDrawPoint(x, y, EMPTY_CHAR); //erase flyer from screen
		flyers[flyerIndex]->deleteFlyer();
		isActive = false;
		s[snakeIndex].updateShotsCounter(false);//increase num of shots
	}
  	menu.updateSnakesMessageRow(snakeIndex, s[snakeIndex].getBodySize(), s[snakeIndex].getHowManyShotsAviable());
	return isActive;
}

void SnakesGame::numEaterHitsSnake(int snakeIndex)
{
	if (snakeIndex == 0)
		s[snakeIndex+1].increaseBodySize(); //increase the snake's body size
	else
		s[snakeIndex-1].increaseBodySize(); //increase the snake's body size
	menu.printSnakeHitsNumEater(s[snakeIndex].getShape());
	Sleep(SLEEP_TIME_SHORT);
}

void SnakesGame::resetFlyers()
{
	size_t i;
	int x, y;
	Point tempPoint;
	for (i = 0; i < MAX_FLYERS_ARR_SIZE; i++)	//erase row/col flyers from board
	{
		flyers[i]->reset();
		flyers[i]->getPoint(tempPoint);
		tempPoint.getXY(x, y);
		board.setAndDrawPoint(x, y, EMPTY_CHAR);
	}
	numEater = { Point{ Flyers::ROW, Flyers::COL } };
	rowFlyer1 = { Direction::RIGHT, Point{ Flyers::RF1Col, Flyers::RF1Row }, Color::LIGHTMAGENTA, ROW_FLYER_CHAR, false, true, true };
	rowFlyer2 = { Direction::LEFT, Point{ Flyers::RF2Col, Flyers::RF2Row }, Color::LIGHTMAGENTA, ROW_FLYER_CHAR, false, false, true };

	colFlyer1 = { Direction::UP, Point{ Flyers::CF1Col, Flyers::CF1Row }, Color::LIGHTMAGENTA, COL_FLYER_CHAR, true, false, false };
	colFlyer2 = { Direction::DOWN, Point{ Flyers::CF2Col, Flyers::CF2Row }, Color::LIGHTMAGENTA, COL_FLYER_CHAR, true, true, false };
	if (!numList.empty())
		setTargetFromList(); //update numEater's target
	else
		numEater.endPersuit();
}

void SnakesGame::findAndRemoveFromNumList(Numbers number) 
{
	Point p;
	p = number.getNumPoint();
	findAndRemoveFromNumListHelper(p);
}

void SnakesGame::findAndRemoveFromNumListHelper(Point& p)
{
	Numbers* deletedNumber = nullptr;
	list<Numbers*>::iterator start = numList.begin();
	list<Numbers*>::iterator end = numList.end();
	Point point;
	Numbers target = numEater.getTarget();
	bool targetIsDeleted = false;

	if (p.isEqual(target.getNumPoint()))
		targetIsDeleted = true;

	for (; start != end; ++start)
	{
		point = (*start)->getNumPoint();
		if (p.isEqual(point)) //delete number from numList
		{
			deletedNumber = *start;
			start = numList.erase(start);
			break;
		}
	}
	if (targetIsDeleted)
	{
		numEater.endPersuit();
		if (numList.size() > 0)//if the number was the num eater's target - find new one
			setTargetFromList();	
	}
}

void SnakesGame::setTargetFromList() 
{
	int minDistance, distance;
	Numbers closestNumber;
	list<Numbers*>::iterator itr = numList.begin();
	list<Numbers*>::iterator end = numList.end();
	Numbers temp;

	minDistance = numEater.dist(*(*itr)); //calculate the first distance
	closestNumber = *(*itr); //set first number as closest
	++itr;

	for (; itr != end; ++itr)
	{
		temp = *(*itr);
		distance = numEater.dist(temp);
		if (distance < minDistance)
		{
			minDistance = distance; 
			closestNumber = *(*itr); //save the number
		}
	}
	numEater.setCurrDistance(minDistance); //save dist in eater
	numEater.setTarget(closestNumber); //save target in eater
}

void SnakesGame::updateNumList() //clear the list and update with new currect numbers
{
	if (!numList.empty())
		numList.clear();
	for (int i = 0; i < numArrSize; i++)
	{
		if (numArr[i].isNumCorrect())
			numList.push_back(&numArr[i]);
	}
	numEater.endPersuit();
	if (!numList.empty())
		setTargetFromList(); //find new target to numEater
}

