//============================================================================
// Name        : Giera.cpp
// Author      : Piotr Poskart
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ncurses.h>
#include "Board.h"
using namespace std;

int main()
{
	initscr();
	noecho();
	printw("Siema! Witam w mojej apce..");
	move(20,25);
	printw("Costam");
//	mvprintw(10, 20, "Cos napisane nizej i w prawo...");

	Board plansza;


	refresh();
	int c;
	while((c = getch()) != 27)
	{
		move(10,10);
		printw("Keycode: %d, you pressed %c key..", c, c);
		move(0,0);
		printw("Write something (ESC to escape): ");
		refresh();
		plansza.drawFrame();
	}

	endwin();
	return 0;
}
