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
	wtimeout(gameWindow, 0);

	int c = 0;
	fflush(stdin);
	while (1)
	{
		timeCounter = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			) - beginTime;
		
		c = wgetch(gameWindow);
		//fflush(stdin);
		
		plansza.keyHandle(c);
		plansza.update(timeCounter);

		if (c == 's')
			plansza.showItems();

		if (c == 27)
			break;
		if (!(timeCounter.count() % 50))
		{
			wclear(gameWindow);
			plansza.drawFrame();
			plansza.drawItems();
		}
	}
}

void Game::saveGame()
{

}

void Game::loadGame()
{

}