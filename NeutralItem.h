/*
 * NeutralItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef NEUTRALITEM_H_
#define NEUTRALITEM_H_
#include "GameItem.h"

class NeutralItem : public GameItem
{
public:
	NeutralItem();
	virtual ~NeutralItem();

	virtual bool move(const int & dx, const int & dy) = 0;
	virtual bool setPosition(position & coords) = 0;
};

#endif /* NEUTRALITEM_H_ */
