#pragma once
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "Bullet.h"
#include "EnemyItem.h"

class EnemyBullet : virtual public EnemyItem, virtual public Bullet
{
public:
	EnemyBullet();
	EnemyBullet(const int & xx, const int & yy);
	virtual ~EnemyBullet();

	GameItem * clone() { return new EnemyBullet(*this); };
	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;
	bool updatePosition(long int ms);

protected:
	int speed;

private:
	static char mainCharacter;

};


#endif