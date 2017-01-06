#include "MyBullet.h"

char MyBullet::mainCharacter = '^';

MyBullet::MyBullet(void) : speed(1) 
{
	movementSpeed = 15;
	firepower = 50;
}

MyBullet::MyBullet(const int & xx, const int & yy) : speed(1)
{
	movementSpeed = 15;
	firepower = 50;
	coordinates.x = xx;
	coordinates.y = yy;
}

MyBullet::~MyBullet() {}

/*
	Return MyBullet value if destroyed.
*/
int MyBullet::getPointsForDestroy(void)
{
	return 0;
}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * MyBullet::getPointsOfBody(void) const
{
	return nullptr;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int MyBullet::getNumberOfBodyPoints(void) const
{
	return 0;
}

/*
	Returns main character for this game item.
*/
char MyBullet::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Method updatePosition(long int ms) updates position of MyBullet.
*/
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
			return *itemIt;
	}	
	return nullptr;
}
