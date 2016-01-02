#include "EnemyBullet.h"

char EnemyBullet::mainCharacter = '!';

EnemyBullet::EnemyBullet(void) : speed(1) 
{
	movementSpeed = 12;
}

EnemyBullet::EnemyBullet(const int & xx, const int & yy) : speed(1)
{
	movementSpeed = 12;
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

GameItem * EnemyBullet::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	//check all items in board for this bullet
	gameItemIterator itemIt = boardItems->begin();
	for (; itemIt != boardItems->end(); itemIt++)
	{
		if ((*itemIt) == this)
			continue;
		//check if bullet hit in the middle of the item
		if (	((*itemIt)->whetherCollideWithPosition(&((this)->getPosition())))	
			&&	(dynamic_cast<EnemyItem *>(*itemIt) == nullptr))
		{
			boardItems->remove(*itemIt);
			return this;
		}
	}

	return nullptr;
}
