/*
 * Board.cpp
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#include "Board.h"

char Board::frameHorizontalLine[] = { 0 };

Board::Board()
{
	// TODO Auto-generated constructor stub

}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

void Board::init(void)
{
	srand(time(NULL));
	for (int i = 0; i < boardSizeX; i++)
		frameHorizontalLine[i] = frameCharacter;
	frameHorizontalLine[boardSizeX] = '\0';
}

void Board::clear(void)
{

}

void Board::drawFrame(void)
{
	mvprintw(0, 0, "\r%s\n", frameHorizontalLine);

	int i;
	for (i = 1; i < boardSizeY; i++)
	{
		mvprintw(i, 0, "\r%c", frameCharacter);
		mvprintw(i, boardSizeX - 1, "%c", frameCharacter);
	}
	mvprintw(i,0,"\r%s\n", frameHorizontalLine);
	refresh();
}

void Board::initialize(void)
{
	EnemyShip * nowy = new EnemyShip(30, 15);
	enemies.push_back(nowy);

	EnemyShip * nowy1 = new EnemyShip(60, 15);
	enemies.push_back(nowy1);

	Stone * kamien = new Stone(45, 22);
	enemies.push_back(kamien);

	randomEnemy(0.8);
}



void Board::drawItems(void)
{
	vector<GameItem *>::iterator i = enemies.begin();
	for (; i != enemies.end(); i++)
	{
		cout << (*(*i));
	}
}

void Board::randomEnemy(double difficultyLevel)
{
	//get random x form range 0 - difficultyLevel;
	double x = (rand() % 100) / 100 * difficultyLevel;		
	//get random y form range 0 - difficultyLevel;
	double y = (rand() % 100) / 100 * difficultyLevel;
	//get floor of min(x,y)
	int enemyIndex = (int) min(x, y);	

	GameItem * nowy = NULL;
	switch (enemyIndex)
	{
	case 0:
		nowy = new Stone();
		break;
	case 1:
		nowy = new EnemyShip();
		break;
	case 2:
		break;
	default:
		break;
	}

	if (nowy != NULL)
	{
		int N = nowy->getNumberOfBodyPoints();
		position * bodyPointsTable = nowy->getPointsOfBody();

		int maxXSizeOfItem = max(maxXofPoints(bodyPointsTable, N),
			(-1)*minXofPoints(bodyPointsTable, N));

		position nowa{ (rand() % (boardSizeX - 2 - 2 * maxXSizeOfItem) + 1 + maxXSizeOfItem),
			(-1)*minYofPoints(bodyPointsTable, N) + 1 };

		nowy->setPosition(nowa);
		enemies.push_back(nowy);
	}
}

double & Board::probabilityDistributeFunction(double & x, double & difficulty)
{
	double out = (-x + difficulty);
	return out;
}
