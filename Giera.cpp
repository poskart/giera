//============================================================================
// Name        : Giera.cpp
// Author      : Piotr Poskart
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <curses.h>

#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{
	initscr();
	noecho();
	Game gra;
	//_CrtSetBreakAlloc(195);
	Menu menu(gra);
	while(menu.start());

	refresh();
	endwin();

	return 0;
}
