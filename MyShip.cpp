/*
 * MyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "MyShip.h"

char MyShip::mainCharacter = 'H';
position MyShip::pointsOfBody[numberOfBodyPoints] = { { 0, -1 },{ 1, 0 },{ -1, 0 } };

MyShip::MyShip() : MyShip::MyShip({ gameBoardSizeX / 2, gameBoardSizeY - 1 + minYofPoints(pointsOfBody, numberOfBodyPoints) }) {}

MyShip::MyShip(position & newPos)
{
	coordinates = newPos;
	score = 0;
	gMissilePtr = nullptr;
}

MyShip::MyShip(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
	score = 0;
	gMissilePtr = nullptr;
}

MyShip::~MyShip() {}

/*
	Return MyShip value if destroyed.
*/
int MyShip::getPointsForDestroy(void)
{
	return 0;
}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * MyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int MyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

/*
	Returns main character for this game item.
*/
char MyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Returns ptr to guided missile if exists, nullptr otherwise.
*/
GuidedMissile * MyShip::getGuidedMissilePtr(void)
{
	return gMissilePtr;
}

/*
	Sets ptr to guided missile with new value of newMissile.
*/
void MyShip::setGuidedMissilePtr(GuidedMissile * newMissile)
{
	gMissilePtr = newMissile;
}

/*
	Method updateColision(...) handles collision with the other game items
*/
GameItem * MyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

/*
	Method updatePosition(long int ms) updates position of this item.
*/
bool MyShip::updatePosition(long int ms)
{
	return true;
}

/*
	Add points to total score.
*/
void MyShip::AddPoints(int value)
{
	score += value;
}

/*
	Return total score.
*/
int MyShip::getScore(void)
{
	return score;
}

/*
	Return score attribute reference.
*/
int & MyShip::getScoreRef(void)
{
	return score;
}
