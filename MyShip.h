/*
 * MyShip.h
 *
 *  Created on: 5 gru 2015
 *      Author: piotr
 */

#ifndef MYSHIP_H_
#define MYSHIP_H_

#include "Spaceship.h"
#include "NeutralItem.h"

class MyShip : public NeutralItem, public Spaceship
{
public:
	MyShip();
	MyShip(position & newPos);
	MyShip(const int & xx, const int & yy);
	virtual ~MyShip();

	bool move(const int & dx, const int & dy);
	bool setPosition(position & coords);
	void draw(ostream & where) const;
	position * getPointsOfBody(void);
	int getNumberOfBodyPoints(void);

protected:
	bool whetherCollideWithPosition(const position & potentialCollide);
	bool whetherCollideWithWalls(MyShip & jakis);
	bool whetherCollideWithWallsX(MyShip & jakis);
	bool whetherCollideWithWallsY(MyShip & jakis);

private:
	const static short int numberOfBodyPoints = 3;
	/**
	* array that describes size of the gameItem in each of direction
	* form the middle of Item (forward, right, back, left)
	*/
	static position pointsOfBody[numberOfBodyPoints];
	static char mainCharacter;

};

#endif /* MYSHIP_H_ */
