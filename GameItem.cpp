/*
 * GameItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "GameItem.h"

WINDOW * GameItem::win = NULL;

GameItem::GameItem()
{
	lifePercentage = 100;
	movementSpeed = 1;
	lastUpdateTime = 0;
	firepower = 0;
}

GameItem::~GameItem()
{
	// TODO Auto-generated destructor stub
}

void GameItem::setCommonWindow(WINDOW * fromGame)
{
	GameItem::win = fromGame;
}

void GameItem::setLife(int & percent)
{
	lifePercentage = percent;
}

int GameItem::getLife(void)
{
	return lifePercentage;
}

bool GameItem::isAlive(void)
{
	return lifePercentage > 0;
}

int GameItem::getFirepower(void)
{
	return firepower;
}

position GameItem::getPosition(void)
{
	return coordinates;
}

void GameItem::forcePosition(position & nowa)
{
	coordinates = nowa;
}

ostream & operator<< (ostream & os, const GameItem & gi)
{
	gi.draw(os);
	return os;
}

bool GameItem::move(const int & dx, const int & dy)
{
	bool wasMoved = false;
	GameItem *obstacle = clone();
	position aux{ this->coordinates.x + dx, this->coordinates.y + dy };
	obstacle->forcePosition(aux);
	if (!obstacle->whetherCollideWithWallsX(*obstacle) && dx != 0)
	{
		coordinates.x += dx;
		wasMoved = true;
	}
	if (!obstacle->whetherCollideWithWallsY(*obstacle) && dy != 0)
	{
		coordinates.y += dy;
		wasMoved = true;
	}
	delete obstacle;

	return wasMoved;
}

bool GameItem::setPosition(position & coords)
{
	coordinates = coords;
	return true;
}


bool GameItem::whetherCollideWithPosition(const position * potentialCollide)
{
	if ((*potentialCollide) == coordinates)
		return true;
	position * tmpPos = getPointsOfBody();
	for (int i = 0; i < getNumberOfBodyPoints(); i++, tmpPos++)
	{
		if ((*potentialCollide) == ((*tmpPos) + coordinates))//((potentialCollide->x == (tmpPos->x + coordinates.x)) && (potentialCollide->y == (tmpPos->y + coordinates.y)))
			return true;
	}
	return false;
}

bool GameItem::whetherCollideWithWalls(const GameItem & jakis) const
{
	if (whetherCollideWithWallsX(jakis) && whetherCollideWithWallsY(jakis))
		return true;
	return false;
}

bool GameItem::whetherCollideWithWallsX(const GameItem & jakis) const
{
	if (isXinsideBoard(jakis.coordinates.x + maxXofPoints(getPointsOfBody(), getNumberOfBodyPoints()))
		&& isXinsideBoard(jakis.coordinates.x + minXofPoints(getPointsOfBody(), getNumberOfBodyPoints())))
		return false;
	return true;
}

bool GameItem::whetherCollideWithWallsY(const GameItem & jakis) const
{
	if (isYinsideBoard(jakis.coordinates.y + maxYofPoints(getPointsOfBody(), getNumberOfBodyPoints()))
		&& isYinsideBoard(jakis.coordinates.y + minYofPoints(getPointsOfBody(), getNumberOfBodyPoints())))
		return false;
	return true;
}

void GameItem::draw(ostream & where) const  
{
	mvwprintw(win, coordinates.y, coordinates.x, "%c", this->getMainCharacter());
	position * pos = this->getPointsOfBody();
	if (pos != nullptr)
	{
		for (int i = 0; i < this->getNumberOfBodyPoints(); i++)
		{
			mvwprintw(win, coordinates.y + pos[i].y, coordinates.x + pos[i].x,
				"%c", this->getMainCharacter());
		}
	}
}

bool GameItem::updatePosition(long int ms)
{
	return false;
}

GameItem * GameItem::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

bool isXinsideBoard(int x)
{
	if( x < (gameBoardSizeX -1) && x > 0)
		return true;
	return false;
}

bool isYinsideBoard(int y)
{
	if( y < (gameBoardSizeY - 1) && y > 0)
		return true;
	return false;
}

int maxXofPoints(position * array, const int & N)
{
	int maxX = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].x > maxX)
			maxX = array[i].x;
	return maxX;
}

int maxYofPoints(position * array, const int & N)
{
	int maxY = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].y > maxY)
			maxY = array[i].y;
	return maxY;
}

int minXofPoints(position * array, const int & N)
{
	int minX = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].x < minX)
			minX = array[i].x;
	return minX;
}

int minYofPoints(position * array, const int & N)
{
	int minY = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].y < minY)
			minY = array[i].y;
	return minY;
}
