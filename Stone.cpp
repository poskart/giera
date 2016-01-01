/*
 * Stone.cpp
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#include "Stone.h"

char Stone::mainCharacter = '@';

position Stone::pointsOfBody[numberOfBodyPoints] = { {0, 1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1} };
position Stone::pointsWhenDisappears[numberOfBodyPointsWhenDisappears] = { { 1, 0 }, { -1, 0 } };

Stone::Stone() : Stone::Stone({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

Stone::Stone(position & newPos)
{
	coordinates = newPos;
	movementSpeed = 6;
}

Stone::Stone(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
	movementSpeed = 6;
}

Stone::~Stone(){}

position * Stone::getPointsOfBody(void) const
{
	if (!isStoneAtTheEndOfTheBoard())
		return pointsOfBody;
	else
		return pointsWhenDisappears;
	return pointsOfBody;
}
int Stone::getNumberOfBodyPoints(void) const
{
	if (!isStoneAtTheEndOfTheBoard())
		return numberOfBodyPoints;
	else
		return numberOfBodyPointsWhenDisappears;
	return numberOfBodyPoints;
}

char Stone::getMainCharacter(void) const 
{
	return mainCharacter;
}

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

bool Stone::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	//check all items in board for each of bullets
	position * middlePos = &(myShip->getPosition());
	if (this->whetherCollideWithPosition(middlePos))
		return true;
	position * tmpPos = (myShip->getPointsOfBody());
	int numberOfPoints = myShip->getNumberOfBodyPoints();
	for (int i = 0; i < numberOfPoints; i++, tmpPos++)
	{
		position tmp = (*tmpPos) + (*middlePos);
		if (this->whetherCollideWithPosition(&tmp))
			return true;
	}
	return false;
}

bool Stone::isStoneAtTheEndOfTheBoard(void) const
{
	return coordinates.y == (gameBoardSizeY - 2);
}
