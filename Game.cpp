#include "Game.h"

Game::Game()
{
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
	move(5, 5);
	printw("%c",A_REVERSE);
	refresh();
	plansza.drawItems();
	refresh();

	int c;
	while ((c = getch()) != 27)
	{
		clear();
		plansza.drawFrame();
		plansza.drawItems();

		move(10, 10);
		printw("Keycode: %d, you pressed %c key..", c, c);
	}
}

void Game::saveGame()
{

}

void Game::loadGame()
{

}