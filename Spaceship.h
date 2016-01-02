/*
 * Spaceship.h
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#include "GameItem.h"
#include "Bullet.h"
#include "EnemyItem.h"
#include "NeutralItem.h"

class Spaceship : public virtual GameItem
{
public:

	Spaceship();
	virtual ~Spaceship();
	void draw(ostream & where) const;

	virtual Spaceship * getInstance() = 0;
	virtual direction getAttackDirection() = 0;
	template<typename T>
	void shoot(T * nowy, gameItemContainer * boardItems);
	void shoot(gameItemContainer * boardItems);
	void killed(gameItemIterator it);

protected:
	mutable gameItemContainer bullets;
	bool shootEnabled;
};

#endif /* SPACESHIP_H_ */
