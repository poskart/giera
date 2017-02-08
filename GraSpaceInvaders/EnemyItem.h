/*
 * EnemyItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef ENEMYITEM_H_
#define ENEMYITEM_H_
#include "GameItem.h"

class EnemyItem : virtual public GameItem
{
public:
	EnemyItem();
	virtual ~EnemyItem();
	static void updateTargetPosition(GameItem * target);
	bool isTargetWithinRange(int xRangeArea);
protected:
	static direction attackDir;
	static position targetPos;
};

#endif /* ENEMYITEM_H_ */
