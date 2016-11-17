#include "Game.h"

Game::Game()
{
	gameWindow = newwin(gameBoardSizeY, gameBoardSizeX+30, 0, 0);
	noecho();
	cbreak();
	// turn on keypad translation for terminal
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
	plansza = new Board();
	plansza->init(gameWindow);
	plansza->initialize();
	plansza->drawFrame();
	plansza->drawItems();
	// do not block keyboard for gameWindow - 
	// read each of characters separately
	wtimeout(gameWindow, 0);

	int c = 0;
	fflush(stdin);
	while (1)
	{
		timeCounter = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			) - beginTime;
		
		// no delay mode enabled
		nodelay(gameWindow, true);
		c = wgetch(gameWindow);
		
		// update ship behavior
		plansza->keyHandle(c);

		// check if MyShip not destroyed
		if (!(plansza->update(timeCounter)))
			break;

		if (c == 's')
			plansza->showItems();

		if (!(timeCounter.count() % 50))
		{
			wclear(gameWindow);
			plansza->drawFrame();
			plansza->drawItems();
		}
		if (c == 27)
			break;
	}
	
	mvwprintw(gameWindow, 18, 40, "KONIEC GRY...");
	wrefresh(gameWindow);
	delete plansza;
	getch();
}

void Game::saveGame()
{

}

void Game::loadGame()
{

}