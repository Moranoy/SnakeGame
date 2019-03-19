#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

enum  ScreenBorders { MENU_ROWS = 4, GAME_ROWS = 21, SCREEN_COLS = 80, SCREEN_ROWS = 24};

enum RangeType { low, medium, high };

enum KEYS { ESC = 27 };

enum  Sizes { INIT_SIZE = 3, MAX_BODY_SIZE = 15, DIR_KEYS = 4, INIT_SHOTS = 5, MAX_LINE_SIZE = 101};

enum GameSizes { SNAKES_ARR_SIZE = 2, MAX_NUM_EATERS = 1, MAX_ROW_FLYERS = 2, MAX_COL_FLYERS = 2, MAX_FLYERS_ARR_SIZE = 5, DIR_ARR_SIZE = 4, MAX_SHOT_ARR_SIZE = 5, MAX_NUM_ARR_SIZE = 60, MAX_NUM_VAL = 169 };

enum Timers { TIME2SPAWN = 5, SPARKLE_TIMES = 10, TIME2WAIT = 25, SLEEP_TIME_SHORT = 1000, SLEEP_TIME = 3000 };

enum StartPos { START_POSITION_ROW = 9, START_POSITION_COL1 = 10, START_POSITION_COL2 = 70, MESSAGE_POSITION = 30, MESSAGE_ROW = 2 };




//--------------screen signs--------------
#define SNAKE_1_SHOT 'z'
#define SNAKE_2_SHOT 'n'
#define SNAKE_1_CHAR '@'
#define SNAKE_2_CHAR '#'
#define EMPTY_CHAR ' '
#define SHOT_CHAR '*'
#define ROW_FLYER_CHAR '!'
#define COL_FLYER_CHAR '$'
#define NUM_EATER_CHAR '%'
#define RANDOM_SIGN '%'
#define IS_NUMBER 'n'
#define IS_SNAKE 's'
#define IS_SHOT 't'
#define IS_COL_FLYER 'c'
#define IS_ROW_FLYER 'r'
#define IS_NUM_EATER 'e'




//------------miscellaneous---------
#define ADD '+'
#define SUB '-'
#define MULTIPLY '*'
#define DIV '/'
#define EMPTY_NUM_STR "___"


#define RANGE_TYPE_NUMBER 3
#define CALC_ERROR -1
#define DUMMY_INT -1
#define NO_SNAKE_FIRED -1

#endif