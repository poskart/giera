/*
 * EnemyShip.h
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#ifndef ENEMYSHIP_H_
#define ENEMYSHIP_H_

#include "EnemyItem.h"
#include "Spaceship.h"
#include "EnemyBullet.h"

class EnemyShip : public EnemyItem, public Spaceship
{
public:

	EnemyShip();
	EnemyShip(position & newPos);
	EnemyShip(const int & xx, const int & yy);
	virtual ~EnemyShip();

	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;
	bool updatePosition(long int ms);
	
	//check whether bullets hits sth, if nyShip hit then return tru e
	bool updateColision(gameItemContainer * boardItems, GameItem * myShip);
	bool whetherBulletHit(gameItemContainer * boardItems, GameItem * myShip);

	GameItem * clone() { return new EnemyShip(*this); };
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

#endif /* ENEMYSHIP_H_ */
