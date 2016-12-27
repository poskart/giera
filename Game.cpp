#include "Game.h"

Game::Game()
{
	gameWindow = newwin(gameBoardSizeY, gameBoardSizeX + scoreDisplaySize, 0, 0);
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
		// Update time counter
		timeCounter = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			) - beginTime;
		
		// no delay mode enabled
		nodelay(gameWindow, true);

		// Wait for key pressed
		c = wgetch(gameWindow);
		
		// update ship behavior
		plansza->keyHandle(c);

		// check if MyShip not destroyed
		if (!(plansza->update(timeCounter)))
			break;

		// Update board view
		wclear(gameWindow);
		plansza->drawFrame();
		plansza->drawItems();

		if (c == 's')
			plansza->showItems();
		if (c == 27)
			break;

		Sleep(20);
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