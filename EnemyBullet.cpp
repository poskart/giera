#include "EnemyBullet.h"

char EnemyBullet::mainCharacter = '!';
int EnemyBullet::pointsForDestroy = 40;

EnemyBullet::EnemyBullet(void) : speed(1) 
{
	firepower = 50;
	movementSpeed = 20;
}

EnemyBullet::EnemyBullet(const int & xx, const int & yy) : EnemyBullet::EnemyBullet()
{
	coordinates.x = xx;
	coordinates.y = yy;
}

EnemyBullet::~EnemyBullet() {}

int EnemyBullet::getPointsForDestroy(void)
{
	return pointsForDestroy;
}

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


/*
	Method updateColision(), for each item on the board, checks whether EnemyBullet hit in it,
	removes hit item, and returns this pointer if there was collision with sth, or nullptr
	if there was no collision.
*/
GameItem * EnemyBullet::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	//check all items in board for this bullet
	gameItemIterator itemIt = boardItems->begin();
	if (itemIt == boardItems->end())
		return nullptr;
	
	for (; itemIt != boardItems->end(); itemIt++)
	{
		// Check if I am not myself
		if ((*itemIt) == this)
			continue;
		// If bullet hit in the middle of item & it is not enemyItem
		if (((*itemIt)->whetherCollideWithPosition(&((this)->getPosition())))
			&& (dynamic_cast<EnemyItem *>(*itemIt) == nullptr))
			return *itemIt;
	}
	if (myShip->whetherCollideWithPosition(&((this)->getPosition())))
		return myShip;

	return nullptr;
}
