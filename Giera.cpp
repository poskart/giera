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

using namespace std;

void drawFrame(void)
{
	move(0,0);
	cout<<"\r*********************************************************"<<endl;
	for(int i = 0 ; i < 20 ; i++)
		cout<<"\r*\t\t\t\t\t\t\t*"<<endl;
	cout<<"\r*********************************************************"<<endl;
}

int main()
{
	initscr();
	noecho();
	printw("Siema! Witam w mojej apce..");
	move(20,25);
	printw("Costam");
	move(2,2);
	//	mvprintw(10, 20, "Cos napisane nizej i w prawo...");

	Board plansza;
	move(0,0);
	plansza.initialize();
	plansza.drawFrame();
	plansza.drawItems();

	//refresh();
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

	char ch;
	cout<<"Tutaj znaki: "<<endl;
	for(int i = 0 ; i < 255; i++)
		cout<<ch++<<" ";
	endwin();
	return 0;
}
