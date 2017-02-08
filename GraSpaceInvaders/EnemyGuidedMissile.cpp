#include "EnemyGuidedMissile.h"

char EnemyGuidedMissile::mainCharacter = 'V';

EnemyGuidedMissile::EnemyGuidedMissile()
{
	movementSpeed = 18;
	horizontalSpeed = 10;
	lastHorizontalUpdateTime = 0;
}

EnemyGuidedMissile::EnemyGuidedMissile(const int & xx, const int & yy)
{
	movementSpeed = 18;
	coordinates.x = xx;
	coordinates.y = yy;
	horizontalSpeed = 10;
	lastHorizontalUpdateTime = 0;
}

EnemyGuidedMissile::~EnemyGuidedMissile() {}

/*
	Returns main character for this game item.
*/
char EnemyGuidedMissile::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Method updatePosition(long int ms) updates position of EnemyGuidedMissile
	to track myShip.
*/
bool EnemyGuidedMissile::updatePosition(long int ms)
{
	static int targetDx = 0;
	bool outOfTheBoard = false;
	if (targetDx == 0 &&
		ms - lastHorizontalUpdateTime > gameSlowness / horizontalSpeed)
	{
		int positionToTargetError = targetPos.x - coordinates.x;
		double  kp = 50 / gameBoardSizeX;
		if (positionToTargetError < 0)
			targetDx = (int)(kp*positionToTargetError) - 1;
		else if (positionToTargetError > 0)
			targetDx = (int)(kp*positionToTargetError) + 1;
		lastHorizontalUpdateTime = ms;
	}
	if (ms - lastUpdateTime > gameSlowness / movementSpeed)
	{
		lastUpdateTime = ms;
		if (!move(0, speed*attackDir))
			outOfTheBoard = true;
		if (!isXinsideBoard(getPosition().x + targetDx)
			|| !isXinsideBoard(getPosition().x - targetDx))
			outOfTheBoard = true;
		else
			move(targetDx, 0);
		targetDx = 0;
	}
	return !outOfTheBoard;
}