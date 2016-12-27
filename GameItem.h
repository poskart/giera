/*
 * GameItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef GAMEITEM_H_
#define GAMEITEM_H_

#include "settings.h"

class GameItem
{
public:
	GameItem();
	virtual ~GameItem();

	static void setCommonWindow(WINDOW * fromGame);

	position getPosition(void);
	void setLife(int & percent);
	int getLife(void);
	bool isAlive(void);
	int getFirepower(void);
	virtual position * getPointsOfBody(void) const = 0;
	virtual int getNumberOfBodyPoints(void) const = 0;
	virtual char getMainCharacter(void) const  = 0;

	bool move(const int & dx, const int & dy);
	bool setPosition(position & coords);
	bool whetherCollideWithPosition(const position * potentialCollide);
	bool whetherCollideWithWalls(const GameItem & jakis) const;
	bool whetherCollideWithWallsX(const GameItem & jakis) const;
	bool whetherCollideWithWallsY(const GameItem & jakis) const;
	virtual void draw(ostream & where) const ;
	virtual bool updatePosition(long int ms);
	virtual GameItem * updateColision(gameItemContainer * boardItems, GameItem * myShip);

protected:
	position coordinates;
	int lifePercentage;
	int movementSpeed;
	int firepower;
	long int lastUpdateTime;
	static WINDOW * win;

	void forcePosition(position & nowa);
};

/**
 * virtual operator << use functions GameItem::draw()
 * @param os - ostream (cout)
 * @param gi - instance of class derived from GameItem
 * @return os - ostream (cout)
 */

ostream & operator<< (ostream & os, const GameItem & gi);

bool isXinsideBoard(int x);
bool isYinsideBoard(int y);
int maxXofPoints(position * array, const int & N);
int maxYofPoints(position * array, const int & N);
int minXofPoints(position * array, const int & N);
int minYofPoints(position * array, const int & N);

#endif /* GAMEITEM_H_ */
