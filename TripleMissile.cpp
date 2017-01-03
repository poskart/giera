#include "tripleMissile.h"

char TripleMissile::mainCharacter = 'o';

TripleMissile::TripleMissile()
{
	movementSpeed = 20;
	horizontalSpeed = 0;
	lastHorizontalUpdateTime = 0;
}

TripleMissile::TripleMissile(const int & xx, const int & yy)
{
	movementSpeed = 20;
	horizontalSpeed = 0;
	lastHorizontalUpdateTime = 0;
	coordinates.x = xx;
	coordinates.y = yy;
}

TripleMissile::~TripleMissile() {}

void TripleMissile::setHorizontalSpeed(double spd)
{
	horizontalSpeed = spd;
}

char TripleMissile::getMainCharacter(void) const
{
	return mainCharacter;
}

bool TripleMissile::updatePosition(long int ms)
{
	int horizontalMove = 0;
	bool outOfTheBoard = false;
	// If it's time to update horizontal movement
	if (horizontalSpeed != 0.0)
	{
		if (ms - lastHorizontalUpdateTime > (int)(gameSlowness / abs(horizontalSpeed)))
		{
			horizontalMove = (horizontalSpeed > 0) ? 1 : -1;
			lastHorizontalUpdateTime = ms;
			if (!isXinsideBoard(getPosition().x + horizontalMove)
				|| !isXinsideBoard(getPosition().x - horizontalMove))
				outOfTheBoard = true;
			else
				move(horizontalMove, 0);
		}
	}
	if (ms - lastUpdateTime > gameSlowness / movementSpeed)
	{
		lastUpdateTime = ms;
		if (!move(horizontalMove, speed*attackDir))
			outOfTheBoard = true;
	}
	return !outOfTheBoard;
}