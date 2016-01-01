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
		//jf there will not be a chance to update position
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

bool Spaceship::handleBulletsHits(gameItemContainer * boardItems)
{
	//check all items in board for each of bullets
	bool wasColision = false;
	bool wasAtLeastOneHit = false;
	position * tmpPos;
	int numberOfPoints = 0;
	gameItemIterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		gameItemIterator itemIt = boardItems->begin();
		for (; itemIt != boardItems->end(); itemIt++)
		{
			//check if bullet hit in the middle of the item
        	if ((*itemIt)->whetherCollideWithPosition(&((*bulletIt)->getPosition())))
 			{
				wasColision = true;
				wasAtLeastOneHit = true;
				//save deserted bullets
				if((dynamic_cast<Spaceship *>(*(itemIt)) != nullptr) )
	 	 			saveBulletsAfterKilled(boardItems, dynamic_cast<Spaceship *>(*(itemIt)));
				boardItems->remove(*itemIt);
				break;
			}
		}
		//delete bullet
		if (wasColision)
		{
			bulletIt = bullets.erase(bulletIt);
			wasColision = false;
			continue;
		}
		bulletIt++;
	}
	return wasAtLeastOneHit;
}
//check if bullet hit in 
bool Spaceship::saveBulletsAfterKilled(gameItemContainer * boardItems, Spaceship * killed)
 {
	bool wasAnySaved = false;
	for (gameItemIterator it = killed->bullets.begin(); it != killed->bullets.end(); it++)
	{ 
 		boardItems->push_back(*it);
		wasAnySaved = true;
	}
	return wasAnySaved;
}
