/*
 * SimpleEnemyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "SimpleEnemyShip.h"

char SimpleEnemyShip::mainCharacter = 'x';
position SimpleEnemyShip::pointsOfBody[numberOfBodyPoints] = {{0, 1}, {1, 0}, {-1, 0}};
int SimpleEnemyShip::pointsForDestroy = 200;

int SimpleEnemyShip::maxYfrontLinePosition = boardSizeY / 2;

SimpleEnemyShip::SimpleEnemyShip() : SimpleEnemyShip::SimpleEnemyShip({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

SimpleEnemyShip::SimpleEnemyShip(position & newPos) : SimpleEnemyShip::SimpleEnemyShip(newPos.x, newPos.y)	{}

SimpleEnemyShip::SimpleEnemyShip(const int & xx, const int & yy)
{
	previousShootTime = 0;
	betweenShotMeanTime = 1000;
	movementSpeed = 2;
	firepower = 50;
	coordinates.x = xx;
	coordinates.y = yy;
	targetSelfLocatePositionY = rand() % maxYfrontLinePosition;
}

SimpleEnemyShip::~SimpleEnemyShip(){
}

int SimpleEnemyShip::getPointsForDestroy(void)
{
	return pointsForDestroy;
}

position * SimpleEnemyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int SimpleEnemyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char SimpleEnemyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

bool SimpleEnemyShip::updatePosition(long int ms)
{
	if ((ms - lastUpdateTime) > (gameSlowness / movementSpeed))
	{
		int targetDx = 0, targetDy = 0;
		double  kp = 4 / gameBoardSizeX;
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

GameItem * SimpleEnemyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

bool SimpleEnemyShip::shootIfShould(gameItemContainer * boardItems, long int ms)
{
	int shootTimePeriod = (rand() % (2 * betweenShotMeanTime) + 500);
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