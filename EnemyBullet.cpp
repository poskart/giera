#include "EnemyBullet.h"

char EnemyBullet::mainCharacter = '!';

EnemyBullet::EnemyBullet(void) : speed(1) 
{
	movementSpeed = 10;
}

EnemyBullet::EnemyBullet(const int & xx, const int & yy) : speed(1)
{
	movementSpeed = 10;
	coordinates.x = xx;
	coordinates.y = yy;
}

EnemyBullet::~EnemyBullet() {}

position * EnemyBullet::getPointsOfBody(void) const
{
	return nullptr;
}
int EnemyBullet::getNumberOfBodyPoints(void) const
{
	return 0;
}
char EnemyBullet::getMainCharacter(void) const
{
	return mainCharacter;
}

bool EnemyBullet::updatePosition(long int ms)
{
	if (ms - lastUpdateTime > 1000 / movementSpeed)
	{
		if (!move(0, speed*attackDir))
		{
			lastUpdateTime = ms;
			return false;
		}
		lastUpdateTime = ms;
	}
	return true;
}