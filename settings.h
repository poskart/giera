#ifndef SETTINGS_H
#define SETTINGS_H

#include <curses.h>

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <list>

using namespace std;

class GameItem;

// Size of game boards
const int boardSizeX = 100;
const int boardSizeY = 65;

// The same as above + frame thickness
const int gameBoardSizeX = boardSizeX + 2;
const int gameBoardSizeY = boardSizeY + 2;

// Width of the score display
const int scoreDisplaySize = 30;

const int gameSlowness = 1000;	// =>  min movement update frequency = 1/gameSlowness, here: 1 update/s

const int initialInsertNewEnemyMeanTime = 2500;	//ms
const double initialDifficultyLevel = 1.5;

const int initialIncrementDifficultyMeanTime = 1000;

typedef struct
{
	int x, y;
}position;

position operator+(const position & pos1, const position & pos2);
bool operator==(const position & pos1, const position & pos2);

typedef enum
{
	up = -1,
	down = 1
}direction;

typedef std::list<GameItem *> gameItemContainer;
typedef std::list<GameItem *>::iterator gameItemIterator;

#endif
