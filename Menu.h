/*
* Menu.h
*
*  Created on: 08 gru 2015
*      Author: piotr
*/

#ifndef MENU_H
#define MENU_H

#include "Game.h"

const int MENU_WIDTH = 30;
const int MENU_HEIGHT = 12;

class Menu
{
public:
	Menu();
	Menu(Game & gra);
	~Menu();

	bool start(void);
	void printMenu(WINDOW *menu_win, int highlight);
	bool printSaveMenu(void);
	bool printLoadMenu(void);

private:
	WINDOW *menu_win;
	int startx, starty;
	Game * servicedGame;
};

#endif