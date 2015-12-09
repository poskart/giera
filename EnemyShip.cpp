/*
 * EnemyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "EnemyShip.h"

char EnemyShip::mainCharacter = 'x';
position EnemyShip::pointsOfBody[numberOfBodyPoints] = {{0, 1}, {1, 0}, {-1, 0}};

EnemyShip::EnemyShip() : EnemyShip::EnemyShip({boardSizeX/2, minYofPoints(pointsOfBody, numberOfBodyPoints)})	{}

EnemyShip::EnemyShip(position & newPos)
{
	coordinates = newPos;
}

EnemyShip::EnemyShip(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
}

EnemyShip::~EnemyShip(){}


position * EnemyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int EnemyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char EnemyShip::getMainCharacter(void) const
{
	return mainCharacter;
}