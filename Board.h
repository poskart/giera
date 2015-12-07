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

using namespace std;

const char frameCharacter = '#';

class Board
{
public:
	void init();
	void clear();
	void drawFrame(void);
	void drawItems(void);
	void initialize(void);

	Board();
	virtual ~Board();
private:
	vector<GameItem *> enemies;
	vector<GameItem *> neutrals;

	static char frameHorizontalLine[boardSizeX + 1];
	int MySpaceShip;
};

#endif /* BOARD_H_ */
