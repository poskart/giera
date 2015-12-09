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

bool GameItem::isAlive(void)
{
	return lifePercentage != 0;
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

bool isXinsideBoard(int x)
{
	if( x < gameBoardSizeX && x > 0)
		return true;
	return false;
}

bool isYinsideBoard(int y)
{
	if( y < gameBoardSizeY && y > 0)
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
