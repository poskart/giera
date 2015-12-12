/*
 * Board.cpp
 *
 *  Created on: 24 lis 2015
 *      Author: piotr
 */

#include "Board.h"

char Board::frameHorizontalLine[] = { 0 };

Board::Board() {}

Board::Board(WINDOW * fromGame)
{
	win = fromGame;
}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

void Board::init(WINDOW * fromGame)
{
	//initialize random numbers
	srand(time(NULL));

	//initialize frame characters
	for (int i = 0; i < gameBoardSizeX; i++)
		frameHorizontalLine[i] = frameCharacter;
	frameHorizontalLine[gameBoardSizeX] = '\0';

	//initialize WINDOW for this Board
	win = fromGame;
	//initialize WINDOW for all GameItems
	GameItem::setCommonWindow(win);
}

void Board::clear(void)
{

}

void Board::drawFrame()
{
	mvwprintw(win, 0, 0, "\r%s\n", frameHorizontalLine);

	int i;
	for (i = 1; i < gameBoardSizeY -1; i++)
	{
		mvwprintw(win, i, 0, "\r%c", frameCharacter);
		mvwprintw(win, i, gameBoardSizeX - 1, "%c", frameCharacter);
	}
	mvwprintw(win, i, 0, "\r%s\n", frameHorizontalLine);
	wrefresh(win);
}

void Board::initialize(void)
{
	myShip = new MyShip();

	EnemyShip * nowy = new EnemyShip(30, 15);
	boardItems.push_back(nowy);

	EnemyShip * nowy1 = new EnemyShip(60, 15);
	boardItems.push_back(nowy1);

	Stone * kamien = new Stone(45, 22);
	boardItems.push_back(kamien);

	randomEnemy(0.8);
	randomEnemy(1.2);
}



void Board::drawItems()
{
	gameItemIterator i = boardItems.begin();
	for (; i != boardItems.end(); i++)
	{
		cout << (*(*i));
	}
	/*if(enemies.size() != 0)
		enemies.erase(enemies.begin());*/
	cout<<*myShip;
	wrefresh(win);
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

		position nowa{ (rand() % (boardSizeX - 2 * maxXSizeOfItem) + 1 + maxXSizeOfItem),
			(-1)*minYofPoints(bodyPointsTable, N) + 1 };

		nowy->setPosition(nowa);
		boardItems.push_back(nowy);
	}
}

void Board::showItems(void)
{
	int enemyShips = 0, stones = 0;
	gameItemIterator it = boardItems.begin();
	for (; it != boardItems.end(); it++)
	{
		if (dynamic_cast<EnemyShip *>(*it) != nullptr)
			enemyShips++;
		else if (dynamic_cast<Stone *>(*it) != nullptr)
			stones++;
		else;
	}
	mvwprintw(win, 16, 40, "Policzono:");
	mvwprintw(win, 17, 40, "statki wroga: %d", enemyShips);
	mvwprintw(win, 18, 40, "kamienie: %d", stones);
	wrefresh(win);
	getch();
}

void Board::update(chrono::milliseconds & time)
{
	EnemyItem::getTargetPosition(myShip);
	gameItemIterator i = boardItems.begin();
	for (; i != boardItems.end(); i++)
	{
		(*i)->updatePosition(time.count());
	}
	/*if(enemies.size() != 0)
	enemies.erase(enemies.begin());*/
	myShip->updatePosition(time.count());
}

void Board::keyHandle(const int & key)
{
	int dS = 1;
	switch (key)
	{
	case KEY_UP:
		myShip->move(0, -dS);
		break;
	case KEY_DOWN:
		myShip->move(0, dS);
		break;
	case KEY_RIGHT:
		myShip->move(dS, 0);
		break;
	case KEY_LEFT:
		myShip->move(-dS, 0);
		break;
	case CTL_UP:
		myShip->move(0, -3 * dS);
		break;
	case CTL_DOWN:
		myShip->move(0, 3 * dS);
		break;
	case CTL_RIGHT:
		myShip->move(3 * dS, 0);
		break;
	case CTL_LEFT:
		myShip->move(-3 * dS, 0);
		break;
	case ' ':
	{
		position pos = myShip->getPosition();
		Bullet * bul = new MyBullet(pos.x, pos.y);
		myShip->shoot(bul);
		break;
	}
	default:
		refresh();
		break;
	}
}

//double & Board::probabilityDistributeFunction(double & x, double & difficulty)
//{
//	double out = (-x + difficulty);
//	return out;
//}
