/*
*
 * Spaceship.cpp
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#include "Spaceship.h"

Spaceship::Spaceship()
{
	// TODO Auto-generated constructor stub

}

Spaceship::~Spaceship()
{
	// TODO Auto-generated destructor stub
}

template<typename T>
void Spaceship::shoot(T * nowy)
{
	position pos;
	if (getInstance()->getAttackDirection() == up)
		pos = { coordinates.x,
			coordinates.y - 1 + minYofPoints(getPointsOfBody(), getNumberOfBodyPoints()) };
	else
		pos = { coordinates.x,
			coordinates.y + 1 + maxYofPoints(getPointsOfBody(), getNumberOfBodyPoints()) };
	nowy->setPosition(pos);
	bullets.push_back(nowy);
}

void Spaceship::shoot()
{
	Spaceship::shoot(new Bullet());
}

void Spaceship::killed(gameItemIterator it)
{
	bullets.erase(it);
}

void Spaceship::draw(ostream & where) const
{
	GameItem::draw(where);
	const gameItemIterator it = bullets.begin();
	gameItemIterator i = it;
	for (; i != bullets.end(); i++)
	{
		cout << (*(*i));
	}
	wrefresh(win);
}

bool Spaceship::updateBullets(long int ms)
{
	//update bullets
	bool ifAnyOfBullets = false;
	gameItemIterator it = bullets.begin();

	while (it != bullets.end())
	{
		if (!(*it)->updatePosition(ms))
		{
			it = bullets.erase(it);
			continue;
		}
		else
			ifAnyOfBullets = true;
		it++;
	}
	return ifAnyOfBullets;
}