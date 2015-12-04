/*
 * Stone.h
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#ifndef STONE_H_
#define STONE_H_
#include "EnemyItem.h"

class Stone : public EnemyItem
{
public:

	Stone();
	virtual ~Stone();

	bool move(const int & dx, const int & dy);

protected:
	bool whetherCollideWithPosition(const position & potantialCollide);

private:
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static short int sizes[4];

};

#endif /* STONE_H_ */
