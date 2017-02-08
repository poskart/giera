#include "EnemyDestroyer.h"

char EnemyDestroyer::mainCharacter = 'W';
position EnemyDestroyer::pointsOfBody[numberOfBodyPoints] = { { 0, 1 }, {1, 0}, {-1, 0}, { 2, 0 }, { -2, 0 }, {-1, 1}, {1, 1}, {-2, 1}, {2, 1}, {-2, 2}, {2, 2}, {0, 2}, {0, 3} };
int EnemyDestroyer::pointsForDestroy = 1000;

int EnemyDestroyer::maxYfrontLinePosition = boardSizeY * 0.65;

EnemyDestroyer::EnemyDestroyer()
{
	previousShootTime = 0;
	betweenShotMeanTime = 400;
	movementSpeed = 4;
	maxShootingRange = 35;
	firepower = 0;
	roundRobinMissileType = 0;
	targetSelfLocatePositionY = rand() % maxYfrontLinePosition;
}

EnemyDestroyer::EnemyDestroyer(position & newPos) : EnemyDestroyer::EnemyDestroyer()
{
	coordinates.x = newPos.x;
	coordinates.y = newPos.y;
}

EnemyDestroyer::EnemyDestroyer(const int & xx, const int & yy) : EnemyDestroyer::EnemyDestroyer()
{
	coordinates.x = xx;
	coordinates.y = yy;
}

EnemyDestroyer::~EnemyDestroyer()
{
}

/*
	Return EnemyDestroyer value if destroyed.
*/
int EnemyDestroyer::getPointsForDestroy(void)
{
	return pointsForDestroy;
}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * EnemyDestroyer::getPointsOfBody(void) const
{
	return pointsOfBody;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int EnemyDestroyer::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

/*
	Returns main character for this game item.
*/
char EnemyDestroyer::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Method updateColision(...) handles collision with the other game items
*/
GameItem * EnemyDestroyer::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

/*
	Method shootIfShould(...), if it's time to, adds new missile,
	updates proviousShootTime attribute value and disables shooting
	at the end.
*/
bool EnemyDestroyer::shootIfShould(gameItemContainer * boardItems, long int ms)
{
	int shootTimePeriod = (rand() % (2 * betweenShotMeanTime) + 500);
	if (shootEnabled &&
		((ms - previousShootTime) > shootTimePeriod))
	{
		EnemyItem * pocisk;
		// If roundRobinMissileType = 0
		if (roundRobinMissileType == 0)
		{
			pocisk = new EnemyGuidedMissile();
			shoot(pocisk, boardItems, { coordinates.x, coordinates.y + 2});
		}
		// If roundRobinMissileType = 1 v 3 & spaceship not far than 5 units on x axis
		else if (roundRobinMissileType % 2 && 
			isTargetWithinRange(5))
		{
			pocisk = new EnemyBullet();
			shoot(pocisk, boardItems, { coordinates.x - 2, coordinates.y + 3});
		}
		// If roundRobinMissileType = 2 v 4 & spaceship not far than 5 units on x axis
		else if (!(roundRobinMissileType%2) &&
			isTargetWithinRange(5))
		{
			pocisk = new EnemyBullet();
			shoot(pocisk, boardItems, { coordinates.x + 2, coordinates.y + 3});
		}
		roundRobinMissileType = (++roundRobinMissileType) % 5;
		previousShootTime = ms;
		shootEnabled = false;
		return true;
	}
	return false;
}