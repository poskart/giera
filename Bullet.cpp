#include "Bullet.h"

char Bullet::mainCharacter = 'o';

Bullet::Bullet(void) : speed(1) {}

Bullet::Bullet(const int & xx, const int & yy) : speed(1)
{
	coordinates.x = xx;
	coordinates.y = yy;
}

Bullet::~Bullet() {}

position * Bullet::getPointsOfBody(void) const
{
	return nullptr;
}
int Bullet::getNumberOfBodyPoints(void) const
{
	return 0;
}
char Bullet::getMainCharacter(void) const
{
	return mainCharacter;
}

bool Bullet::updatePosition(long int ms)
{
	return false;
}