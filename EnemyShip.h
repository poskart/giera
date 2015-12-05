/*
 * EnemyShip.h
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#ifndef ENEMYSHIP_H_
#define ENEMYSHIP_H_

#include "EnemyItem.h"
#include "Spaceship.h"

class EnemyShip : public EnemyItem, public Spaceship
{
public:
	EnemyShip();
	virtual ~EnemyShip();
};

#endif /* ENEMYSHIP_H_ */
