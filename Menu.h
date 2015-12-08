/*
* Menu.h
*
*  Created on: 08 gru 2015
*      Author: piotr
*/

#ifndef MENU_H
#define MENU_H

#include "Game.h"

const int WIDTH = 30;
const int HEIGHT = 24;

class Menu
{
public:
	Menu();
	Menu(Game & gra);
	~Menu();

	void start(void);
	void print_menu(WINDOW *menu_win, int highlight);

private:
	WINDOW *menu_win;
	int startx, starty;
	Game * servicedGame;
};

#endif