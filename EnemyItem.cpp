/*
 * EnemyItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "EnemyItem.h"

direction EnemyItem::attackDir = down;

position EnemyItem::targetPos = {boardSizeX/2, boardSizeY/2};

EnemyItem::EnemyItem()
{
	// TODO Auto-generated constructor stub

}

EnemyItem::~EnemyItem()
{
	// TODO Auto-generated destructor stub
}

void EnemyItem::getTargetPosition(GameItem * target)
{
	targetPos = target->getPosition();
}

