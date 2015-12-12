/*
 * MyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "MyShip.h"

char MyShip::mainCharacter = '^';

position MyShip::pointsOfBody[numberOfBodyPoints] = { { 0, -1 },{ 1, 0 },{ -1, 0 } };

MyShip::MyShip() : MyShip::MyShip({ gameBoardSizeX / 2, gameBoardSizeY - 1 + minYofPoints(pointsOfBody, numberOfBodyPoints) }) {}

MyShip::MyShip(position & newPos)
{
	coordinates = newPos;
}

MyShip::MyShip(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
}

MyShip::~MyShip() {}

position * MyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int MyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char MyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

bool MyShip::updatePosition(long int ms)
{
	return updateBullets(ms);
}

