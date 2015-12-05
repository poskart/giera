/*
 * GameItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef GAMEITEM_H_
#define GAMEITEM_H_

#include <vector>
#include <iostream>

using namespace std;

//
//	static const int boardSizeX;
//	static const int boardSizeY;

const int boardSizeX = 80;
const int boardSizeY = 25;

typedef struct
{
	int x, y;
}position;

/**
 * enum for array which describes size of Item in each direction
 * from the middle (forward, right, back, left)
 */
enum
{
	forward,
	right,
	back,
	left
};

class GameItem
{
public:


	GameItem();
	virtual ~GameItem();

	virtual bool move(const int & dx, const int & dy) = 0;
	virtual bool setPosition(position & coords) = 0;
	position getPosition(void);
	void setLife(int & percent);
	bool isAlive(void);


protected:
	position coordinates;
	int lifePercentage;

	void forcePosition(position & nowa);
};

bool isXinsideBoard(int x);
bool isYinsideBoard(int y);
int maxXofPoints(position * array, const int & N);
int maxYofPoints(position * array, const int & N);
int minXofPoints(position * array, const int & N);
int minYofPoints(position * array, const int & N);

#endif /* GAMEITEM_H_ */
