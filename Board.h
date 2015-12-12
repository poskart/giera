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
#include "MyBullet.h"
#include "EnemyBullet.h"

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
	void showItems(void);
	void update(chrono::milliseconds & time);
	void keyHandle(const int & key);


	Board();
	Board(WINDOW * fromGame);
	virtual ~Board();
private:
	WINDOW * win;
	gameItemContainer boardItems;
	MyShip * myShip;

	static char frameHorizontalLine[gameBoardSizeX + 1];

	//double & probabilityDistributeFunction(double & x, double & difficulty);
};

#endif /* BOARD_H_ */
