#pragma once
#include "MyBullet.h"

class GuidedMissile : public MyBullet
{
public:
	GuidedMissile();
	GuidedMissile(const int & xx, const int & yy);
	~GuidedMissile();

	char getMainCharacter(void) const;
private:
	static char mainCharacter;
};

