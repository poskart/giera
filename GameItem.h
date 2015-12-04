/*
 * GameItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef GAMEITEM_H_
#define GAMEITEM_H_

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

	virtual bool move(int dx, int dy) = 0;
	virtual bool setPosition(position coords) = 0;
	void setLife(int & percent);
	bool isAlive(void);


protected:
	position coordinates;
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static short int sizes[4];
	int lifePercentage;
};

#endif /* GAMEITEM_H_ */
