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

bool MyShip::move(const int & dx, const int & dy)
{
	bool wasMoved = false;
	MyShip *obstacle = new MyShip(this->coordinates.x + dx, this->coordinates.y + dy);
	if (!obstacle->whetherCollideWithWallsX(*obstacle))
	{
		coordinates.x += dx;
		wasMoved = true;
	}
	if (!obstacle->whetherCollideWithWallsY(*obstacle))
	{
		coordinates.y += dy;
		wasMoved = true;
	}
	delete obstacle;

	return wasMoved;
}

bool MyShip::setPosition(position & coords)
{
	coordinates = coords;
	return true;
}


bool MyShip::whetherCollideWithPosition(const position & potentialCollide)
{
	for (int i = 0; i < numberOfBodyPoints; i++)
		if ((potentialCollide.x == pointsOfBody[i].x) && (potentialCollide.y == pointsOfBody[i].y))
			return true;
	return false;
}

bool MyShip::whetherCollideWithWalls(MyShip & jakis)
{
	if (whetherCollideWithWallsX(jakis) && whetherCollideWithWallsY(jakis))
		return true;
	return false;
}

bool MyShip::whetherCollideWithWallsX(MyShip & jakis)
{
	if (isXinsideBoard(jakis.coordinates.x + maxXofPoints(pointsOfBody, numberOfBodyPoints))
		&& isXinsideBoard(jakis.coordinates.x + minXofPoints(pointsOfBody, numberOfBodyPoints)))
		return false;
	return true;
}

bool MyShip::whetherCollideWithWallsY(MyShip & jakis)
{
	if (isYinsideBoard(jakis.coordinates.y + maxYofPoints(pointsOfBody, numberOfBodyPoints))
		&& isYinsideBoard(jakis.coordinates.y + minYofPoints(pointsOfBody, numberOfBodyPoints)))
		return false;
	return true;
}

void MyShip::draw(ostream & where) const
{
	mvwprintw(win, coordinates.y, coordinates.x, "%c", mainCharacter);
	for (int i = 0; i < numberOfBodyPoints; i++)
	{
		mvwprintw(win, coordinates.y + pointsOfBody[i].y, coordinates.x + pointsOfBody[i].x,
			"%c", mainCharacter);
	}
}

position * MyShip::getPointsOfBody(void)
{
	return pointsOfBody;
}
int MyShip::getNumberOfBodyPoints(void)
{
	return numberOfBodyPoints;
}