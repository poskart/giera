#include "GuidedMissile.h"

char GuidedMissile::mainCharacter = 'A';
bool missileExistsFlag = false;

GuidedMissile::GuidedMissile()
{
	movementSpeed = 15;
}

GuidedMissile::GuidedMissile(const int & xx, const int & yy)
{
	movementSpeed = 15;
	coordinates.x = xx;
	coordinates.y = yy;
}

GuidedMissile::~GuidedMissile() {}

char GuidedMissile::getMainCharacter(void) const
{
	return mainCharacter;
}
