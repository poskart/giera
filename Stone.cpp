/*
 * Stone.cpp
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#include "Stone.h"

char Stone::mainCharacter = '@';
int Stone::pointsForDestroy = 50;
position Stone::pointsOfBody[numberOfBodyPoints] = { {0, 1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1} };
position Stone::pointsWhenDisappears[numberOfBodyPointsWhenDisappears] = { { 1, 0 }, { -1, 0 } };

Stone::Stone() : Stone::Stone({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

Stone::Stone(position & newPos) : Stone::Stone(newPos.x, newPos.y){}

Stone::Stone(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
	movementSpeed = 6;
	firepower = 25;
}

Stone::~Stone(){}

/*
	Return Stone value if destroyed.
*/
int Stone::getPointsForDestroy(void)
{
	return pointsForDestroy;
}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * Stone::getPointsOfBody(void) const
{
	if (!isStoneAtTheEndOfTheBoard())
		return pointsOfBody;
	else
		return pointsWhenDisappears;
	return pointsOfBody;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int Stone::getNumberOfBodyPoints(void) const
{
	if (!isStoneAtTheEndOfTheBoard())
		return numberOfBodyPoints;
	else
		return numberOfBodyPointsWhenDisappears;
	return numberOfBodyPoints;
}

/*
	Returns main character for this game item.
*/
char Stone::getMainCharacter(void) const 
{
	return mainCharacter;
}

/*
	Method updatePosition(long int ms) updates position of Stone.
*/
bool Stone::updatePosition(long int ms)
{
	if (ms - lastUpdateTime > (gameSlowness / movementSpeed))
	{
		if (!move(0, attackDir))
		{
			lastUpdateTime = ms;
			return false;
		}
		lastUpdateTime = ms;
	}
	return true;
}

/*
	Method updateColision(), checks whether Stone hit MyShip, and returns this pointer
	if there was collision with MyShip, or nullptr if there was no collision.
*/
GameItem * Stone::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	// Check if this Stone hit myShip
	position * middlePos = &(myShip->getPosition());
	if (this->whetherCollideWithPosition(middlePos))
		return myShip;
	position * tmpPos = (myShip->getPointsOfBody());
	int numberOfPoints = myShip->getNumberOfBodyPoints();
	for (int i = 0; i < numberOfPoints; i++, tmpPos++)
	{
		position tmp = (*tmpPos) + (*middlePos);
		if (this->whetherCollideWithPosition(&tmp))
			return myShip;
	}
	return nullptr;
}

/*
	Method isStoneAtTheEndOfTheBoard() returns true if Stone reach end of the
	game board (y), false otherwise.
*/
bool Stone::isStoneAtTheEndOfTheBoard(void) const
{
	return coordinates.y == (gameBoardSizeY - 2);
}
