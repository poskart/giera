/*
 * EnemyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "EnemyShip.h"

char EnemyShip::mainCharacter = 'x';
position EnemyShip::pointsOfBody[numberOfBodyPoints] = {{0, 1}, {1, 0}, {-1, 0}};

int EnemyShip::maxYfrontLinePosition = boardSizeY / 2;

EnemyShip::EnemyShip() : EnemyShip::EnemyShip({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

EnemyShip::EnemyShip(position & newPos)
{
	coordinates = newPos;
	previousShootTime = 0;
	betweenShotMeanTime = 1000;
	movementSpeed = 2;
	targetSelfLocatePositionY = rand() % maxYfrontLinePosition;
}

EnemyShip::EnemyShip(const int & xx, const int & yy)
{
	previousShootTime = 0;
	betweenShotMeanTime = 1000;
	movementSpeed = 2;
	coordinates.x = xx;
	coordinates.y = yy;
	targetSelfLocatePositionY = rand() % maxYfrontLinePosition;
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
	if ((ms - lastUpdateTime) > (gameSlowness / movementSpeed))
	{
		int targetDx = 0, targetDy = 0;
		double kp = 4 / gameBoardSizeX;
		int xPositionError = targetPos.x - this->coordinates.x;
		if (xPositionError < 0)
			targetDx = (int)(kp*xPositionError) - 1;
		else if (xPositionError > 0)
			targetDx = (int)(kp*xPositionError) + 1;
		if ((targetSelfLocatePositionY - coordinates.y) != 0)
			targetDy = 1;
		move(targetDx, targetDy);
		lastUpdateTime = ms;

		if (xPositionError < 5 && xPositionError > -5 )
		{
			shootEnabled = true;
		}
	}
	return true;
}

GameItem * EnemyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

bool EnemyShip::shootIfShould(gameItemContainer * boardItems, long int ms)
{
	int shootTimePeriod = (rand() % (2 * betweenShotMeanTime) + 1000);
	if (shootEnabled &&
		((ms - previousShootTime) > shootTimePeriod))
	{
		Bullet * pocisk = new EnemyBullet({ coordinates.x, coordinates.y });
		shoot(pocisk, boardItems);
		previousShootTime = ms;
		shootEnabled = false;
		return true;
	}
	return false;
}