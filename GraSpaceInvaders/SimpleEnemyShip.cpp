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
	maxShootingRange = 5;
	movementSpeed = 2;
	firepower = 50;
	coordinates.x = xx;
	coordinates.y = yy;
	targetSelfLocatePositionY = rand() % maxYfrontLinePosition;
}

SimpleEnemyShip::~SimpleEnemyShip()	{}

/*
	Return SimpleEnemyShip value if destroyed.
*/
int SimpleEnemyShip::getPointsForDestroy(void)
{
	return pointsForDestroy;
}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * SimpleEnemyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int SimpleEnemyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

/*
	Returns main character for this game item.
*/
char SimpleEnemyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Method updatePosition(long int ms) updates position of SimpleEnemyShip.
*/
bool SimpleEnemyShip::updatePosition(long int ms)
{
	if ((ms - lastUpdateTime) > (gameSlowness / movementSpeed))
	{
		int targetDx = 0, targetDy = 0;
		double  kp = 100 / gameBoardSizeX;
		int xPositionError = targetPos.x - this->coordinates.x;
		if (xPositionError < 0)
			targetDx = (int)(kp*xPositionError) - 1;
		else if (xPositionError > 0)
			targetDx = (int)(kp*xPositionError) + 1;
		if ((targetSelfLocatePositionY - coordinates.y) > 0)
			targetDy = 1;
		move(targetDx, targetDy);
		lastUpdateTime = ms;

		this->shootingEnableWhenEnemyInRange(xPositionError);
	}
	return true;
}

/*
	Method updateColision(...) handles collision with the other game items
*/
GameItem * SimpleEnemyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

/*
	Method shootIfShould(...), if it's time to, adds new missile,
	updates proviousShootTime attribute value and disables shooting
	at the end.
*/
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

/*
	Method shootingEnableWhenEnemyInRange(int xPositionError) sets 
	shootEnabled attribute to true when enemy is within range.
*/
bool SimpleEnemyShip::shootingEnableWhenEnemyInRange(int xPositionError)
{
	if (xPositionError < maxShootingRange && xPositionError > -maxShootingRange)
	{
		shootEnabled = true;
		return true;
	}
	return false;
}