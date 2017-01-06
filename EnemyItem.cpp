/*
 * EnemyItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "EnemyItem.h"

direction EnemyItem::attackDir = down;
position EnemyItem::targetPos = {boardSizeX/2, boardSizeY/2};

EnemyItem::EnemyItem()	{}

EnemyItem::~EnemyItem()	{}

/*
	Method updateTargetPosition(GameItem * target) updates
	target position (myShip) position to targetPos attribute.
*/
void EnemyItem::updateTargetPosition(GameItem * target)
{
	targetPos = target->getPosition();
}

/*
	Method isTargetWithinRange(int xRangeArea) returns true if
	target (myShip) is closer than xRangeArea to the left or right
	or within xRangeArea distance from this enemyItem.
*/
bool EnemyItem::isTargetWithinRange(int xRangeArea)
{
	return (targetPos.x - this->coordinates.x < xRangeArea &&
		targetPos.x - this->coordinates.x > -xRangeArea);
}
