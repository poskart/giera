/*
 * Board.cpp
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#include "Board.h"

char Board::frameHorizontalLine[] = { 0 };

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
	for (int i = 0; i < boardSizeX; i++)
		frameHorizontalLine[i] = frameCharacter;
	frameHorizontalLine[boardSizeX] = '\0';
}

void Board::clear(void)
{

}

void Board::drawFrame(void)
{
	::move(0,0);
	printw("\r%s\n", frameHorizontalLine);

	int i;
	for (i = 1; i < boardSizeY; i++)
	{
		::move(i, 0);
		printw("\r%c", frameCharacter);
		::move(i, boardSizeX-1);
		printw("%c", frameCharacter);
	}
	move(i, 0);
	printw("\r%s\n", frameHorizontalLine);
	refresh();
}

void Board::initialize(void)
{
	EnemyShip * nowy = new EnemyShip(30, 15);
	enemies.push_back(nowy);

	EnemyShip * nowy1 = new EnemyShip(60, 15);
	enemies.push_back(nowy1);

	Stone * kamien = new Stone(45, 22);
	enemies.push_back(kamien);
}

void Board::drawItems(void)
{
	vector<GameItem *>::iterator i = enemies.begin();
	for (; i != enemies.end(); i++)
	{
		cout << (*(*i));
	}
}
