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

bool Menu::start(void)
{
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (gameBoardSizeX + scoreDisplaySize - MENU_WIDTH) / 2;
	starty = (gameBoardSizeY - MENU_HEIGHT) / 2;

	menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	printMenu(menu_win, highlight);
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
			refresh();
			break;
		}
		printMenu(menu_win, highlight);
		if (choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	clrtoeol();
	clear();
	refresh();
	switch (choice)
	{
	case 1:
		this->servicedGame->playGame(true);
		return true;
	case 2:
		printSaveMenu();
		return true;
	case 3:
		if(printLoadMenu())
			this->servicedGame->playGame(false);
		return true;
	case 4:
		break;
	case 5:
		this->servicedGame->deleteBoard();
		break;
	}
	return false;
}

void Menu::printMenu(WINDOW *menu_win, int highlight)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	wrefresh(menu_win);
	for (i = 0; i < n_choices; ++i)
	{
		if (highlight == i + 1) /* Highlight the present choice */
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

bool Menu::printSaveMenu()
{
	char fileName[80];
	WINDOW * saveWin = nullptr;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (gameBoardSizeX + scoreDisplaySize - MENU_WIDTH) / 2;
	starty = (gameBoardSizeY - MENU_HEIGHT) / 2;

	saveWin = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
	keypad(saveWin, TRUE);
	refresh();

	box(saveWin, 0, 0);
	wrefresh(saveWin);

	mvwprintw(saveWin, 2, 2, "%s", "Insert file name:");
	echo();
	// get new file Name
	mvwgetnstr(saveWin, 3, 2, fileName, 80);
	noecho();
	wrefresh(saveWin);

	try 
	{
		this->servicedGame->saveGame(fileName);
	}
	catch (std::ofstream::failure e) 
	{
		std::cerr << "Exception opening/reading/closing file in save attempt";
		getch();
		return false;
	}

	mvwprintw(saveWin, 3, 2, "%s", "Game saved...");
	wrefresh(saveWin);
	getch();
	return true;
}

bool Menu::printLoadMenu()
{ 
	char fileName[80];
	WINDOW * saveWin = nullptr;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (gameBoardSizeX + scoreDisplaySize - MENU_WIDTH) / 2;
	starty = (gameBoardSizeY - MENU_HEIGHT) / 2;

	saveWin = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
	keypad(saveWin, TRUE);
	refresh();

	box(saveWin, 0, 0);
	wrefresh(saveWin);

	mvwprintw(saveWin, 2, 2, "%s", "Insert file name:");
	echo();
	// get new file Name
	mvwgetnstr(saveWin, 3, 2, fileName, 80);
	noecho();
	wrefresh(saveWin);

	try
	{
		this->servicedGame->loadGame(fileName);
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Exception opening/reading/closing file in load attempt";
		getch();
		return false;
	}

	mvwprintw(saveWin, 3, 2, "%s", "Game loaded...");
	wrefresh(saveWin);
	getch();
	return true;
}