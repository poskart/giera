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
#include <fstream>

using namespace chrono;

class Game
{
public:
	Game();
	virtual ~Game();

	void saveGame(const char * fileName);
	void loadGame(const char * fileName);
	void playGame(bool newGame);
	void deleteBoard();
	void initialize();
private:
	WINDOW * gameWindow;
	Board * plansza;
	milliseconds timeCounter, beginTime;
};

streamsize getSizeFromEnumType(gameObjectTypes typeOfObj);

#endif /* GAME_H_ */