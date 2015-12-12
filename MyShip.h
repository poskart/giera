/*
 * MyShip.h
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#ifndef MYSHIP_H_
#define MYSHIP_H_

#include "Spaceship.h"
#include "NeutralItem.h"

class MyShip : virtual public NeutralItem, virtual public Spaceship
{
public:
	MyShip();
	MyShip(position & newPos);
	MyShip(const int & xx, const int & yy);
	virtual ~MyShip();
	GameItem * clone() { return new MyShip(*this); };
	Spaceship * getInstance() { return this; };
	direction getAttackDirection() { return attackDir; };


	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;

	bool updatePosition(long int ms);

protected:

private:
	const static short int numberOfBodyPoints = 3;
	/**
	* array that describes size of the gameItem in each of direction
	* form the middle of Item (forward, right, back, left)
	*/
	static position pointsOfBody[numberOfBodyPoints];
	static char mainCharacter;
};

#endif /* MYSHIP_H_ */
