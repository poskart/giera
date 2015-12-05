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

class EnemyShip : public EnemyItem, public Spaceship
{
public:

	EnemyShip();
	EnemyShip(position & newPos);
	EnemyShip(const int & xx, const int & yy);
	virtual ~EnemyShip();

	bool move(const int & dx, const int & dy);
	bool setPosition(position & coords);
	void draw(ostream & where) const;

protected:
	bool whetherCollideWithPosition(const position & potentialCollide);
	bool whetherCollideWithWalls(EnemyShip & jakis);
	bool whetherCollideWithWallsX(EnemyShip & jakis);
	bool whetherCollideWithWallsY(EnemyShip & jakis);

private:
	const static short int numberOfBodyPoints = 3;
	/**
	 * array that describes size of the gameItem in each of direction
	 * form the middle of Item (forward, right, back, left)
	 */
	static position pointsOfBody[numberOfBodyPoints];
};

#endif /* ENEMYSHIP_H_ */
