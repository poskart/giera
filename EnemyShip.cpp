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

		if (xPositionError < 5 && xPositionError > -5 && (ms - previousShootTime) > (rand()%(2*betweenShotMeanTime) + 500))
		{
			Bullet * pocisk = new EnemyBullet({ coordinates.x, coordinates.y });
			shoot(pocisk);
			previousShootTime = ms;
		}
	}
	return updateBullets(ms);
}

bool EnemyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return whetherBulletHit(boardItems, myShip);
}

bool EnemyShip::whetherBulletHit(gameItemContainer * boardItems, GameItem * myShip)
{
	handleBulletsHits(boardItems);

	//check whether bullets hit myShip
	gameItemIterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		if (myShip->whetherCollideWithPosition(&((*bulletIt)->getPosition())))
		{
			bullets.erase(bulletIt);
			return true;
		}
		bulletIt++;
	}
	return false;
}
