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
#include "GuidedMissile.h"

class MyShip : virtual public NeutralItem, virtual public Spaceship
{
public:
	MyShip();
	MyShip(position & newPos);
	MyShip(const int & xx, const int & yy);
	virtual ~MyShip();

	bool loseHealth(const int & health);
	GuidedMissile * getGuidedMissilePtr(void);
	void setGuidedMissilePtr(GuidedMissile *);
	Spaceship * getInstance() { return this; };
	direction getAttackDirection() { return attackDir; };
	void AddPoints(int value);
	int getScore(void);
	int & getScoreRef(void);

	int getPointsForDestroy(void);
	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;

	bool updatePosition(long int ms);
	GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);
protected:
	GuidedMissile * gMissilePtr;
private:
	int score;
	const static short int numberOfBodyPoints = 3;

	static position pointsOfBody[numberOfBodyPoints];
	static char mainCharacter;
};

#endif /* MYSHIP_H_ */
