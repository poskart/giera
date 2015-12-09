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

	bool move(const int & dx, const int & dy);
	virtual bool setPosition(position & coords) = 0;
	position getPosition(void);
	void setLife(int & percent);
	bool isAlive(void);
	virtual void draw(ostream & where) const = 0;
	virtual position * getPointsOfBody(void) = 0;
	virtual int getNumberOfBodyPoints(void) = 0;


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
