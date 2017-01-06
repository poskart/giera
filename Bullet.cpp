#include "Bullet.h"

char Bullet::mainCharacter = 'o';

Bullet::Bullet(void) : speed(1) {}

Bullet::Bullet(const int & xx, const int & yy) : speed(1)
{
	coordinates.x = xx;
	coordinates.y = yy;
}

Bullet::~Bullet() {}

/*
	Return points of array which tell where on the board item's body is now.
*/
position * Bullet::getPointsOfBody(void) const
{
	return nullptr;
}

/*
	Return points count which the graphical representation
	of the item takes, minus 1 (without main position character).
*/
int Bullet::getNumberOfBodyPoints(void) const
{
	return 0;
}

/*
	Returns main character for this game item.
*/
char Bullet::getMainCharacter(void) const
{
	return mainCharacter;
}

/*
	Method updatePosition(long int ms) updates position of Bullet.
*/
bool Bullet::updatePosition(long int ms)
{
	return false;
}