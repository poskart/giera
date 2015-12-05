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
	virtual ~MyShip();
};

#endif /* MYSHIP_H_ */
