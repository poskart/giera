/*
 * Board.h
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <curses.h>
#include "NeutralItem.h"
#include "Spaceship.h"
#include "Stone.h"
#include "EnemyShip.h"
#include "MyShip.h"

using namespace std;

const char frameCharacter = '#';

class Board
{
public:
	void init(WINDOW * fromGame);
	void clear();
	void drawFrame(void);
	void drawItems(void);
	void initialize(void);
	void randomEnemy(double difficultyLevel);
	void Board::update(chrono::milliseconds & time, const int & key);

	Board();
	Board(WINDOW * fromGame);
	virtual ~Board();
private:
	WINDOW * win;
	vector<GameItem *> enemies;
	vector<GameItem *> neutrals;
	GameItem * myShip;

	static char frameHorizontalLine[gameBoardSizeX + 1];

	//double & probabilityDistributeFunction(double & x, double & difficulty);
};

#endif /* BOARD_H_ */
