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
#include "SimpleEnemyShip.h"
#include "MyShip.h"
#include "MyBullet.h"
#include "EnemyBullet.h"
#include "GuidedMissile.h"
#include "TripleMissile.h"
#include "EnemyDestroyer.h"
#include "EnemyGuidedMissile.h"

using namespace std;

class Game;
const char frameCharacter = '#';

class Board
{
	friend class Game;
public:
	void init(WINDOW * fromGame);
	void drawFrame(void);
	void drawItems(void);
	void initializeItems(void);
	void showStatistic(void);
	bool collisionDetect(void);
	void randomEnemy(double difficultyLevel);
	bool update(chrono::milliseconds & time);
	void keyHandle(const int & key);
	void updateMovementsAndAttack(chrono::milliseconds & time);
	void insertEnemy(chrono::milliseconds & time);
	void clear(void);
	void showInfo(int gameTimeMs);

	Board();
	Board(WINDOW * fromGame);
	virtual ~Board();

protected:
	double difficultyLevel;
	int insertNewEnemyMeanTime;

private:
	WINDOW * win;
	gameItemContainer boardItems;
	MyShip * myShip;

	static char frameHorizontalLine[gameBoardSizeX + 1];

	long int prevInsertTime;
	int newInsertTime;
	long int incrementDifficultyPrevTime;
	int incrementDifficultyMeanTime;
	//double & probabilityDistributeFunction(double & x, double & difficulty);
};

#endif /* BOARD_H_ */
