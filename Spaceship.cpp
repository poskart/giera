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
	shootEnabled = false;
}

Spaceship::~Spaceship()
{
	// TODO Auto-generated destructor stub
}

template<typename T>
void Spaceship::shoot(T * nowy, gameItemContainer * boardItems)
{
	position pos;
	if (getInstance()->getAttackDirection() == up)
		pos = { coordinates.x,
			coordinates.y - 1 + minYofPoints(getPointsOfBody(), getNumberOfBodyPoints()) };
	else
		pos = { coordinates.x,
			coordinates.y + 1 + maxYofPoints(getPointsOfBody(), getNumberOfBodyPoints()) };
	nowy->setPosition(pos);
	boardItems->push_back(nowy);
}

void Spaceship::shoot(gameItemContainer * boardItems)
{
	Spaceship::shoot(new Bullet(), boardItems );
}

void Spaceship::draw(ostream & where) const
{
	GameItem::draw(where);
	wrefresh(win);
}