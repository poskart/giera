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

bool Stone::move(const int & dx, const int & dy)
{
	bool wasMoved = false;
	Stone *obstacle = new Stone(this->coordinates.x + dx, this->coordinates.y + dy);
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

bool Stone::setPosition(position & coords)
{
	coordinates = coords;
	return true;
}


bool Stone::whetherCollideWithPosition(const position & potentialCollide)
{
	for(int i = 0 ; i < numberOfBodyPoints ; i++)
		if(	(potentialCollide.x == pointsOfBody[i].x)	&& (potentialCollide.y == pointsOfBody[i].y)	)
			return true;
	return false;
}

bool Stone::whetherCollideWithWalls(Stone & jakis)
{
	if(	whetherCollideWithWallsX(jakis) && whetherCollideWithWallsY(jakis)	)
		return true;
	return false;
}

bool Stone::whetherCollideWithWallsX(Stone & jakis)
{
	if(isXinsideBoard(jakis.coordinates.x + maxXofPoints(pointsOfBody, numberOfBodyPoints))
			&& isXinsideBoard(jakis.coordinates.x + minXofPoints(pointsOfBody, numberOfBodyPoints)) )
		return false;
	return true;
}

bool Stone::whetherCollideWithWallsY(Stone & jakis)
{
	if(isYinsideBoard(jakis.coordinates.y + maxYofPoints(pointsOfBody, numberOfBodyPoints))
			&& isYinsideBoard(jakis.coordinates.y + minYofPoints(pointsOfBody, numberOfBodyPoints)) )
		return false;
	return true;
}

void Stone::draw(ostream & where) const
{
	::move(coordinates.y, coordinates.x);
	printw("%c", mainCharacter);
	for(int i = 0 ; i < numberOfBodyPoints ; i++)
	{
		::move(coordinates.y + pointsOfBody[i].y, coordinates.x + pointsOfBody[i].x);
		printw("%c",mainCharacter);
	}
}

position * Stone::getPointsOfBody(void)
{
	return pointsOfBody;
}
int Stone::getNumberOfBodyPoints(void)
{
	return numberOfBodyPoints;
}
