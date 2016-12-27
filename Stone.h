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
	Stone(position & newPos);
	Stone(const int & xx, const int & yy);
	virtual ~Stone();

	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;

	bool updatePosition(long int ms);
	GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);

protected:

private:
	const static short int numberOfBodyPoints = 5;
	const static short int numberOfBodyPointsWhenDisappears = 2;

	static char mainCharacter;
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static position pointsOfBody[numberOfBodyPoints];
	static position pointsWhenDisappears[numberOfBodyPointsWhenDisappears];

	bool isStoneAtTheEndOfTheBoard(void) const;
};

#endif /* STONE_H_ */
