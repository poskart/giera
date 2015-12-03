/*
 * Board.h
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <ncurses.h>
using namespace std;

class Board
{
public:
	void init();
	void clear();
	void drawFrame(void);

	Board();
	virtual ~Board();
};

#endif /* BOARD_H_ */
