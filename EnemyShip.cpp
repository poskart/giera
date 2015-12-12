/*
 * EnemyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "EnemyShip.h"

char EnemyShip::mainCharacter = 'x';
position EnemyShip::pointsOfBody[numberOfBodyPoints] = {{0, 1}, {1, 0}, {-1, 0}};

EnemyShip::EnemyShip() : EnemyShip::EnemyShip({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

EnemyShip::EnemyShip(position & newPos)
{
	coordinates = newPos;
	previousShootTime = 0;
	betweenShotMeanTime = 2000;
	movementSpeed = 1;
}

EnemyShip::EnemyShip(const int & xx, const int & yy)
{
	previousShootTime = 0;
	betweenShotMeanTime = 2000;
	movementSpeed = 1;
	coordinates.x = xx;
	coordinates.y = yy;
}

EnemyShip::~EnemyShip(){}


position * EnemyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int EnemyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char EnemyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

bool EnemyShip::updatePosition(long int ms)
{
	if ((ms - lastUpdateTime) > (1000/movementSpeed))
	{
		double kp = 4 / gameBoardSizeX;
		int xPositionError = targetPos.x - this->coordinates.x;
		if (xPositionError < 0)
			move(int(kp*xPositionError) - 1, 0);
		else if (xPositionError > 0)
			move(int(kp*xPositionError) + 1, 0);
		lastUpdateTime = ms;

		if (xPositionError < 2 && xPositionError > -2 && (ms - previousShootTime) > (rand()%(2*betweenShotMeanTime) + 500))
		{
			Bullet * pocisk = new EnemyBullet({ coordinates.x, coordinates.y });
			shoot(pocisk);
			previousShootTime = ms;
		}
	}

	return updateBullets(ms);
}
