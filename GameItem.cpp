/*
 * GameItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "GameItem.h"

GameItem::GameItem()
{

}

GameItem::~GameItem()
{
	// TODO Auto-generated destructor stub
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
