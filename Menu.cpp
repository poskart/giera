#include "Menu.h"
#include <iostream>

using namespace std;

char *choices[] = {
	"Play the game",
	"Save game",
	"Load game",
	"Choice 4",
	"Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

Menu::Menu() {}

Menu::Menu(Game & gra)
{
	servicedGame = &gra;
}

Menu::~Menu() {}

void Menu::start(void)
{
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while (1)
	{
		c = wgetch(menu_win);
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			break;
		default:
			mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
			refresh();
			break;
		}
		print_menu(menu_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	clear();
	refresh();
	switch (choice)
	{
	case 1:
	{
		this->servicedGame->playGame();
		break;
	}
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}

}

void Menu::print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	wrefresh(menu_win);
	for (i = 0; i < n_choices; ++i)
	{
		if (highlight == i + 1) /* High light the present choice */
		{
			wattron(menu_win, A_BOLD);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_BOLD);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}