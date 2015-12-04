/*
 * Stone.cpp
 *
 *  Created on: 4 gru 2015
 *      Author: piotr
 */

#include "Stone.h"

short int Stone::sizes[4] = {1,2,3,4};

Stone::Stone()
{
	// TODO Auto-generated constructor stub

}

Stone::~Stone()
{
	// TODO Auto-generated destructor stub
}

bool Stone::move(const int & dx, const int & dy)
{
	if(dx > 0)
	{
		if(	(coordinates.x + sizes[right] + dx)	 < boardSizeX)
		{
			return true;
		}


	}
}

bool Stone::whetherCollideWithPosition(const position & potantialCollide)
{
	if(potantialCollide.x < (coordinates.x + sizes[right])
			&& potantialCollide.x > (coordinates.x - sizes[left])
			&& potantialCollide.y > (coordinates.y - sizes[back])
			&& potantialCollide.y < (coordinates.y - sizes[forward])
			)
	return true;
}
