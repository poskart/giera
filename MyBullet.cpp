#include "MyBullet.h"

char MyBullet::mainCharacter = '^';

MyBullet::MyBullet(void) : speed(2) 
{
	movementSpeed = 3;
}

MyBullet::MyBullet(const int & xx, const int & yy) : speed(2)
{
	movementSpeed = 3;
	coordinates.x = xx;
	coordinates.y = yy;
}

MyBullet::~MyBullet() {}

position * MyBullet::getPointsOfBody(void) const
{
	return nullptr;
}
int MyBullet::getNumberOfBodyPoints(void) const
{
	return 0;
}
char MyBullet::getMainCharacter(void) const
{
	return mainCharacter;
}

bool MyBullet::updatePosition(long int ms)
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