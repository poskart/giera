/*
 * NeutralItem.h
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#ifndef NEUTRALITEM_H_
#define NEUTRALITEM_H_
#include "GameItem.h"

class NeutralItem : virtual public GameItem
{
public:
	NeutralItem();
	virtual ~NeutralItem();
};

#endif /* NEUTRALITEM_H_ */
