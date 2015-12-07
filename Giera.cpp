//============================================================================
// Name        : Giera.cpp
// Author      : Piotr Poskart
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <curses.h>

#include "Board.h"
using namespace std;

using namespace std;

int main()
{
	initscr();
	noecho();
	//	mvprintw(10, 20, "Cos napisane nizej i w prawo...");

	Board plansza;
	plansza.init();
	move(0,0);
	plansza.initialize();
	plansza.drawFrame();
	refresh();
	plansza.drawItems();
	refresh();

	int c;
	while((c = getch()) != 27)
	{
		clear();
		plansza.drawFrame();
		plansza.drawItems();

		move(10,10);
		printw("Keycode: %d, you pressed %c key..", c, c);
	}

	
	/*char ch = 0;
	cout<<"Tutaj znaki: "<<endl;
	for (int i = 0; i < 56; i++)
	{
		cout << ch++ << " " << i << endl;
	}*/
	refresh();
	endwin();

	return 0;
}
