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

/*
	Method updateColision(), for each item on the board, checks whether MyBullet hit in it, 
	removes hit item, and returns this pointer if there was collision with sth, or nullptr 
	if there was no collision.
*/
GameItem * MyBullet::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	GameItem * itemToRemove;
	gameItemIterator itemIt = boardItems->begin();
	if (itemIt == boardItems->end())
		return nullptr;
	// For each of the item in the board, check if I MyBullet hit in it
	for (; itemIt != boardItems->end(); itemIt++)
	{
		if ((*itemIt) == this)
			continue;
		//check if bullet hit in the middle of the item
		if ((*itemIt)->whetherCollideWithPosition(&((this)->getPosition())))
		{	
			itemToRemove = *itemIt;
			boardItems->erase(itemIt);
			delete itemToRemove;
			return this;
		}
	}	
	return nullptr;
}
