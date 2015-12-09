#include "Game.h"

Game::Game()
{
	gameWindow = newwin(gameBoardSizeY, gameBoardSizeX, 0, 0);
	noecho();
	cbreak();
	keypad(gameWindow, TRUE);
	beginTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::playGame(void)
{
	plansza.init(gameWindow);
	plansza.initialize();
	plansza.drawFrame();
	plansza.drawItems();
	wtimeout(gameWindow, 100);

	int c = 0;
	fflush(stdin);
	while (1)
	{
		timeCounter = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			) - beginTime;
		
		c = wgetch(gameWindow);
		fflush(stdin);
		
		plansza.update(timeCounter, c);
		if (c != 0) {
			mvwprintw(gameWindow, 12, 12, "Czas : %d", timeCounter / (1000));
			mvwprintw(gameWindow, 13, 12, "Tutaj jest c: %c", c);
		}

		if (c == 27)
			break;
		wclear(gameWindow);
		plansza.drawFrame();
		plansza.drawItems();

		mvwprintw(gameWindow, 10, 10, "Keycode: %d, you pressed %c key..", (int)c, c);
	}
}

void Game::saveGame()
{

}

void Game::loadGame()
{

}