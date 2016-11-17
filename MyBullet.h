#pragma once
#ifndef MYBULLET_H
#define MYBULLET_H
#include "Bullet.h"
#include "NeutralItem.h"

class MyBullet : virtual public NeutralItem, virtual public Bullet
{
public:
	MyBullet();
	MyBullet(const int & xx, const int & yy);
	virtual ~MyBullet();

	GameItem * clone() { return new MyBullet(*this); };
	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;
	bool updatePosition(long int ms);
	GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);

protected:
	int speed;

private:
	static char mainCharacter;

};


#endif