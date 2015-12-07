/*
 * EnemyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "EnemyShip.h"

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

bool EnemyShip::move(const int & dx, const int & dy)
{
	bool wasMoved = false;
	EnemyShip *obstacle = new EnemyShip(this->coordinates.x + dx, this->coordinates.y + dy);
	if(!obstacle->whetherCollideWithWallsX(*obstacle))
	{
		coordinates.x += dx;
		wasMoved = true;
	}
	if(!obstacle->whetherCollideWithWallsY(*obstacle))
	{
		coordinates.y += dy;
		wasMoved = true;
	}
	delete obstacle;

	return wasMoved;
}

bool EnemyShip::setPosition(position & coords)
{
	coordinates = coords;
	return true;
}


bool EnemyShip::whetherCollideWithPosition(const position & potentialCollide)
{
	for(int i = 0 ; i < numberOfBodyPoints ; i++)
		if(	(potentialCollide.x == pointsOfBody[i].x)	&& (potentialCollide.y == pointsOfBody[i].y)	)
			return true;
	return false;
}

bool EnemyShip::whetherCollideWithWalls(EnemyShip & jakis)
{
	if(	whetherCollideWithWallsX(jakis) && whetherCollideWithWallsY(jakis)	)
		return true;
	return false;
}

bool EnemyShip::whetherCollideWithWallsX(EnemyShip & jakis)
{
	if(isXinsideBoard(jakis.coordinates.x + maxXofPoints(pointsOfBody, numberOfBodyPoints))
			&& isXinsideBoard(jakis.coordinates.x + minXofPoints(pointsOfBody, numberOfBodyPoints)) )
		return false;
	return true;
}

bool EnemyShip::whetherCollideWithWallsY(EnemyShip & jakis)
{
	if(isYinsideBoard(jakis.coordinates.y + maxYofPoints(pointsOfBody, numberOfBodyPoints))
			&& isYinsideBoard(jakis.coordinates.y + minYofPoints(pointsOfBody, numberOfBodyPoints)) )
		return false;
	return true;
}

void EnemyShip::draw(ostream & where) const
{
	::move(coordinates.y, coordinates.x);
	printw("v");
	for(int i = 0 ; i < numberOfBodyPoints ; i++)
	{
		::move(coordinates.y + pointsOfBody[i].y, coordinates.x + pointsOfBody[i].x);
		printw("v");
	}
}
