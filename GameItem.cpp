/*
 * GameItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "GameItem.h"

GameItem::GameItem()
{
	// TODO Auto-generated constructor stub

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
