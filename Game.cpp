#include "Game.h"

Game::Game()
{
	gameWindow = newwin(boardSizeY, boardSizeX, 0, 0);
	keypad(gameWindow, TRUE);
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::playGame(void)
{
	plansza.init();
	move(0, 0);
	plansza.initialize();
	plansza.drawFrame();
	plansza.drawItems();
	refresh();

	int c = 0;
	char kk;
	while ((kk = cin.get()) != 'p')//((c = getch()) != 27)
	{
		cin.putback(kk);
		c = wgetch(gameWindow);
		if (c != 0) {
			printw("Tutaj jest c: %c", c);
			//break;
		}
		//clear();
		plansza.drawFrame();
		plansza.drawItems();

		move(10, 10);
		printw("Keycode: %d, you pressed %c key..", (int)kk, kk);
	}
	mvprintw(18, 18, "Klawisz %d", (int)kk);
	getch();
}

void Game::saveGame()
{

}

void Game::loadGame()
{

}