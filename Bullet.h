#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "GameItem.h"

class Bullet : virtual public GameItem
{
public:
	Bullet();
	Bullet(const int & xx, const int & yy);
	virtual ~Bullet();

	int getPointsForDestroy(void) { return 0; }
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