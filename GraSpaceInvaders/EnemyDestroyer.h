#pragma once
#include "SimpleEnemyShip.h"
#include "EnemyItem.h"
#include "EnemyGuidedMissile.h"
class EnemyDestroyer : public SimpleEnemyShip
{
public:
	EnemyDestroyer();
	EnemyDestroyer(position & newPos);
	EnemyDestroyer(const int & xx, const int & yy);
	~EnemyDestroyer();

	int getPointsForDestroy(void);
	position * getPointsOfBody(void) const;
	int getNumberOfBodyPoints(void) const;
	char getMainCharacter(void) const;

	//check whether bullets hits sth, if myShip hits then returns true
	GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);
	bool shootIfShould(gameItemContainer * boardItems, long int ms);

private:
	const static short int numberOfBodyPoints = 13;
	/**
	* array that describes size of the gameItem in each of direction
	* form the middle of Item (forward, right, back, left)
	*/
	static position pointsOfBody[numberOfBodyPoints];
	static char mainCharacter;
	static int pointsForDestroy;

	static int maxYfrontLinePosition;
	int roundRobinMissileType;
};

