/*
 * GameItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef GAMEITEM_H_
#define GAMEITEM_H_

#include <curses.h>

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;

const int boardSizeX = 120;
const int boardSizeY = 50;

//The same as above + frame thickness
const int gameBoardSizeX = boardSizeX + 2;
const int gameBoardSizeY = boardSizeY + 2;

typedef struct
{
	int x, y;
}position;

/**
 * enum for array which describes size of Item in each direction
 * from the middle (forward, right, back, left)
 */

class GameItem
{
public:
	

	GameItem();
	virtual ~GameItem();

	static void setCommonWindow(WINDOW * fromGame);

	position getPosition(void);
	void setLife(int & percent);
	bool isAlive(void);
	virtual GameItem * clone() = 0 ;
	virtual position * getPointsOfBody(void) const = 0;
	virtual int getNumberOfBodyPoints(void) const = 0;
	virtual char getMainCharacter(void) const  = 0;

	bool move(const int & dx, const int & dy);
	bool setPosition(position & coords);
	bool whetherCollideWithPosition(const position & potentialCollide);
	bool whetherCollideWithWalls(GameItem & jakis);
	bool whetherCollideWithWallsX(GameItem & jakis);
	bool whetherCollideWithWallsY(GameItem & jakis);
	void draw(ostream & where) const ;


protected:
	position coordinates;
	int lifePercentage;
	static WINDOW * win;
	static int * cod;

	void forcePosition(position & nowa);
};

/**
 * virtual operator << use functions GameItem::draw()
 * @param os - ostream (cout)
 * @param gi - instance of class derived from GameItem
 * @return os - ostream (cout)
 */

ostream & operator<< (ostream & os, const GameItem & gi);

bool isXinsideBoard(int x);
bool isYinsideBoard(int y);
int maxXofPoints(position * array, const int & N);
int maxYofPoints(position * array, const int & N);
int minXofPoints(position * array, const int & N);
int minYofPoints(position * array, const int & N);

#endif /* GAMEITEM_H_ */
