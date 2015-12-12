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
class Spaceship : public virtual GameItem
{
public:

	Spaceship();
	virtual ~Spaceship();
	void draw(ostream & where) const;

	virtual Spaceship * getInstance() = 0;
	virtual direction getAttackDirection() = 0;
	template<typename T>
	void shoot(T * nowy);
	void shoot(void);
	void killed(gameItemIterator it);

	bool updateBullets(long int ms);

protected:
	mutable gameItemContainer bullets;
};

#endif /* SPACESHIP_H_ */
