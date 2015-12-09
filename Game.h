/*
* Game.h
*
*  Created on: 7 gru 2015
*      Author: piotr
*/

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Stone.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void saveGame();
	void playGame();
	void loadGame();
	
private:
	WINDOW * gameWindow;
	Board plansza;
};

#endif /* GAME_H_ */