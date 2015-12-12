#ifndef SETTINGS_H
#define SETTINGS_H

#include <curses.h>

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <list>

using namespace std;

class GameItem;

//size of game boards
const int boardSizeX = 100;
const int boardSizeY = 65;

//The same as above + frame thickness
const int gameBoardSizeX = boardSizeX + 2;
const int gameBoardSizeY = boardSizeY + 2;

typedef struct
{
	int x, y;
}position;

typedef enum
{
	up = -1,
	down = 1
}direction;

typedef std::list<GameItem *> gameItemContainer;
typedef std::list<GameItem *>::iterator gameItemIterator;

#endif
