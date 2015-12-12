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
	GameItem * clone() { return new Stone(*this); };

	bool updatePosition(long int ms);

protected:

private:
	const static short int numberOfBodyPoints = 5;
	static char mainCharacter;
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static position pointsOfBody[numberOfBodyPoints];

};

#endif /* STONE_H_ */
