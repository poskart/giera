/*
 * SimpleEnemyShip.h
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#ifndef SimpleEnemyShip_H_
#define SimpleEnemyShip_H_

#include "EnemyItem.h"
#include "Spaceship.h"
#include "EnemyBullet.h"

class SimpleEnemyShip : public EnemyItem, public Spaceship
{
public:

	SimpleEnemyShip();
	SimpleEnemyShip(position & newPos);
	SimpleEnemyShip(const int & xx, const int & yy);
	virtual ~SimpleEnemyShip();

	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;
	bool updatePosition(long int ms);
	
	//check whether bullets hits sth, if nyShip hit then return tru e
	GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);
	bool shootIfShould(gameItemContainer * boardItems, long int ms);

	Spaceship * getInstance() { return this; };
	direction getAttackDirection() { return attackDir; };

protected:
	
	//target Y position of spaceship
	int targetSelfLocatePositionY;

private:
	const static short int numberOfBodyPoints = 3;
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static position pointsOfBody[numberOfBodyPoints];
	static char mainCharacter;

	static int maxYfrontLinePosition;
	long int previousShootTime;
	int betweenShotMeanTime;	//ms
};

#endif /* SimpleEnemyShip_H_ */
