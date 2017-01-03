#pragma once
#include "MyBullet.h"
#include <math.h>

class TripleMissile : public MyBullet
{
public:
	TripleMissile();
	TripleMissile(const int & xx, const int & yy);
	~TripleMissile();

	void setHorizontalSpeed(double spd);
	char getMainCharacter(void) const;
	bool updatePosition(long int ms);

private:
	double horizontalSpeed;
	long int lastHorizontalUpdateTime;

	static char mainCharacter;
};
