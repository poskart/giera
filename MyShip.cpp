/*
 * MyShip.cpp
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#include "MyShip.h"

char MyShip::mainCharacter = '^';

position MyShip::pointsOfBody[numberOfBodyPoints] = { { 0, -1 },{ 1, 0 },{ -1, 0 } };

MyShip::MyShip() : MyShip::MyShip({ gameBoardSizeX / 2, gameBoardSizeY - 1 + minYofPoints(pointsOfBody, numberOfBodyPoints) }) {}

MyShip::MyShip(position & newPos)
{
	coordinates = newPos;
	score = 0;
	gMissilePtr = nullptr;
}

MyShip::MyShip(const int & xx, const int & yy)
{
	coordinates.x = xx;
	coordinates.y = yy;
	score = 0;
	gMissilePtr = nullptr;
}

MyShip::~MyShip() {}

int MyShip::getPointsForDestroy(void)
{
	return 0;
}

position * MyShip::getPointsOfBody(void) const
{
	return pointsOfBody;
}
int MyShip::getNumberOfBodyPoints(void) const
{
	return numberOfBodyPoints;
}

char MyShip::getMainCharacter(void) const
{
	return mainCharacter;
}

bool MyShip::loseHealth(const int & health)
{
	if (this->isAlive())
	{
		int outcomeLife = getLife() - health;
		setLife(outcomeLife);
	}
	return this->isAlive();
}

GuidedMissile * MyShip::getGuidedMissilePtr(void)
{
	return gMissilePtr;
}

void MyShip::setGuidedMissilePtr(GuidedMissile * newMissile)
{
	gMissilePtr = newMissile;
}

GameItem * MyShip::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

bool MyShip::updatePosition(long int ms)
{
	return true;
}

void MyShip::AddPoints(int value)
{
	score += value;
}

int MyShip::getScore(void)
{
	return score;
}

int & MyShip::getScoreRef(void)
{
	return score;
}
