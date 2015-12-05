/*
 * Spaceship.h
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#include "GameItem.h"

class Spaceship : public virtual GameItem
{
public:

	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static short int sizes[4];

	Spaceship();
	virtual ~Spaceship();
};

#endif /* SPACESHIP_H_ */
