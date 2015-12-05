/*
 * Stone.h
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#ifndef STONE_H_
#define STONE_H_
#include "EnemyItem.h"

const short int numberOfBodyPoints = 3;

class Stone : public EnemyItem
{
public:

	Stone();
	Stone(position & newPos);
	Stone(const int & xx, const int & yy);
	virtual ~Stone();

	bool move(const int & dx, const int & dy);
	bool setPosition(position & coords);


protected:
	bool whetherCollideWithPosition(const position & potentialCollide);
	bool whetherCollideWithWalls(Stone & jakis);
	bool whetherCollideWithWallsX(Stone & jakis);
	bool whetherCollideWithWallsY(Stone & jakis);

private:
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static position pointsOfBody[numberOfBodyPoints];

};

#endif /* STONE_H_ */
