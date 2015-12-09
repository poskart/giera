/*
 * Stone.cpp
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#include "Stone.h"

char Stone::mainCharacter = '@';

position Stone::pointsOfBody[numberOfBodyPoints] = { {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, -1} };

Stone::Stone() : Stone::Stone({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

Stone::Stone(position & newPos)
{
	coordinates = newPos;
}

Stone::Stone(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
}

Stone::~Stone(){}

position * Stone::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int Stone::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char Stone::getMainCharacter(void) const 
{
	return mainCharacter;
}