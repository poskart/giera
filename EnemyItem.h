/*
 * EnemyItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef ENEMYITEM_H_
#define ENEMYITEM_H_
#include "GameItem.h"

class EnemyItem : public GameItem
{
public:
	EnemyItem();
	virtual ~EnemyItem();

	virtual bool move(const int & dx, const int & dy) = 0;
	virtual bool setPosition(position & coords) = 0;
};

#endif /* ENEMYITEM_H_ */
