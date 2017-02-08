#include "Menu.h"

using namespace std;

char *choices[] = {
	"Play Shooter",
	"Save game",
	"Load game",
	"Return to game",
	"Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

Menu::Menu() {}

Menu::Menu(Game & gra)
{
	servicedGame = &gra;
}

Menu::~Menu() {}

/*
	Start menu for the new game. Initialize manu window, 
	wait for key pressed and take appropriate action depending 
	on the key pressed.
*/
bool Menu::start(void)
{
	int highlight = 1;
	int choice = 0;
	int c;

	// Initialize ncurses data structures
	initscr();
	// Clear the window
	clear();
	// Do not show input characters
	noecho();
	// Line buffering disabled. pass on everything 
	cbreak();
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
		if (choice != 0)	/* User did a choice, so get out of the infinite loop */
			break;
	}
	clrtoeol();
	clear();
	refresh();
	switch (choice)
	{
	case 1:
		servicedGame->playGame(true);
		return true;
	case 2:
		printSaveMenu();
		return true;
	case 3:
		if (printLoadMenu())
		{
			servicedGame->updateGameTime();
			servicedGame->playGame(false);
		}
		return true;
	case 4:
		if (servicedGame->isBoardInitialized())
		{
			servicedGame->playGame(false);
		}
		return true;
	case 5:
		servicedGame->deleteBoard();
		break;
	}
	return false;
}

/*
	Print menu for the game with currently highlited choice.
*/
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

/*
	Print save menu with prompt for file name and return true if
	file succesfully saved, false otherwise.
*/
bool Menu::printSaveMenu()
{
	char fileName[80];
	WINDOW * saveWin = nullptr;

	// Initialize ncurses data structures
	initscr();
	// Clear the window
	clear();
	// Do not show input characters
	noecho();
	// Line buffering disabled. pass on everything
	cbreak();
	startx = (gameBoardSizeX + scoreDisplaySize - MENU_WIDTH) / 2;
	starty = (gameBoardSizeY - MENU_HEIGHT) / 2;

	saveWin = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
	keypad(saveWin, TRUE);
	refresh();

	// Draw menu borders
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
		mvwprintw(saveWin, 3, 2, "%s", "Exception opening/reading/closing file in save attempt");
		wrefresh(saveWin);
		getch();
		return false;
	}

	mvwprintw(saveWin, 3, 2, "%s", "Game saved...");
	wrefresh(saveWin);
	getch();
	return true;
}

/*
	Print load menu with prompt for file name and return true if
	file succesfully loaded, false otherwise.
*/
bool Menu::printLoadMenu()
{ 
	char fileName[80];
	WINDOW * saveWin = nullptr;

	// Initialize ncurses data structures
	initscr();
	// Clear the window
	clear();
	// Do not show input characters
	noecho();
	// Line buffering disabled. pass on everything
	cbreak();	
	startx = (gameBoardSizeX + scoreDisplaySize - MENU_WIDTH) / 2;
	starty = (gameBoardSizeY - MENU_HEIGHT) / 2;

	saveWin = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
	keypad(saveWin, TRUE);
	refresh();

	// Draw menu borders
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
		mvwprintw(saveWin, 3, 2, "%s", "Exception opening/reading/closing file in load attempt");
		wrefresh(saveWin);
		getch();
		return false;
	}

	mvwprintw(saveWin, 3, 2, "%s", "Game loaded...");
	wrefresh(saveWin);
	getch();
	return true;
}