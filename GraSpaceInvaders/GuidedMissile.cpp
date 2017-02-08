#include "GuidedMissile.h"

char GuidedMissile::mainCharacter = 'A';
bool missileExistsFlag = false;

GuidedMissile::GuidedMissile()
{
	movementSpeed = 15;
	firepower = 100;
}

GuidedMissile::GuidedMissile(const int & xx, const int & yy)
{
	movementSpeed = 15;
	firepower = 100;
	coordinates.x = xx;
	coordinates.y = yy;
}

GuidedMissile::~GuidedMissile() {}

/*
	Returns main character for this game item.
*/
char GuidedMissile::getMainCharacter(void) const
{
	return mainCharacter;
}
