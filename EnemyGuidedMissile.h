#pragma once
#include "EnemyBullet.h"

class EnemyGuidedMissile : public EnemyBullet
{
public:
	EnemyGuidedMissile();
	EnemyGuidedMissile(const int & xx, const int & yy);
	~EnemyGuidedMissile();

	bool updatePosition(long int ms);
	char getMainCharacter(void) const;
private:
	double horizontalSpeed;
	long int lastHorizontalUpdateTime;
	static char mainCharacter;
};

