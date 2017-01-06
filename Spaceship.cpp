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

/*
	Method shoot(T * nowy, gameItemContainer * boardItems) initializes 
	position of new bullet and includes this new item in GameItem main container.
*/
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

/*
	Method shoot(T * nowy, gameItemContainer * boardItems, position pos) initializes
	position of new bullet with pos value and includes this new item in GameItem main container.
*/
void Spaceship::shoot(EnemyItem * nowy, gameItemContainer * boardItems, position pos)
{
	nowy->setPosition(pos);
	boardItems->push_back(nowy);
}

/*
	Shoot with the default weapon
*/
void Spaceship::shoot(gameItemContainer * boardItems)
{
	Spaceship::shoot(new Bullet(), boardItems );
}

/*
	Method draw(ostream & where) draws graphical representation of the
	item to the board.
*/
void Spaceship::draw(ostream & where) const
{
	GameItem::draw(where);
}