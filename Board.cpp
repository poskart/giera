/*
 * Board.cpp
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#include "Board.h"

Board::Board()
{
	// TODO Auto-generated constructor stub

}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

void Board::init(void)
{

}

void Board::clear(void)
{

}

void Board::drawFrame(void)
{
	move(0,0);
	cout<<"\r*********************************************************"<<endl;
	for(int i = 0 ; i < 20 ; i++)
		cout<<"\r*\t\t\t\t\t\t\t*"<<endl;
	cout<<"\r*********************************************************"<<endl;
}
