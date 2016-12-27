#include "EnemyBullet.h"

char EnemyBullet::mainCharacter = '!';

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

	// Save pointer to item I hit on
	GameItem * itemToRemove;
	
	for (; itemIt != boardItems->end(); itemIt++)
	{
		// Check if I am not myself
		if ((*itemIt) == this)
			continue;
		// If bullet hit in the middle of item & it is not enemyItem
		if (	((*itemIt)->whetherCollideWithPosition(&((this)->getPosition())))	
			&&	(dynamic_cast<EnemyItem *>(*itemIt) == nullptr))
		{
			itemToRemove = *itemIt;
			// Remove item wich I hit on
			boardItems->erase(itemIt);
			delete itemToRemove;
			return this;
		}
	}
	if (myShip->whetherCollideWithPosition(&((this)->getPosition())))
		return myShip;

	return nullptr;
}
