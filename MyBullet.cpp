#include "MyBullet.h"

char MyBullet::mainCharacter = '^';

MyBullet::MyBullet(void) : speed(1) 
{
	movementSpeed = 15;
}

MyBullet::MyBullet(const int & xx, const int & yy) : speed(1)
{
	movementSpeed = 15;
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
	if (ms - lastUpdateTime > gameSlowness / movementSpeed)
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

GameItem * MyBullet::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	//check all items in board for each of bullets

	gameItemIterator itemIt = boardItems->begin();
	for (; itemIt != boardItems->end(); itemIt++)
	{
		if ((*itemIt) == this)
			continue;
		//check if bullet hit in the middle of the item
		if ((*itemIt)->whetherCollideWithPosition(&((this)->getPosition())))
		{	
			boardItems->remove(*itemIt);
			return this;
		}
	}
	
	return nullptr;
}
