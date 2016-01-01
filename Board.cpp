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
	difficultyLevel = initialDifficultyLevel;
	insertNewEnemyMeanTime = initialInsertNewEnemyMeanTime;
	prevInsertTime = 1000;
	newInsertTime = 1000;
	incrementDifficultyPrevTime = 1000;
	incrementDifficultyMeanTime = initialIncrementDifficultyMeanTime;
}

Board::Board(WINDOW * fromGame)
{
	win = fromGame;

	difficultyLevel = initialDifficultyLevel;
	insertNewEnemyMeanTime = initialInsertNewEnemyMeanTime;
	prevInsertTime = 1000;
	newInsertTime = 1000;
	incrementDifficultyPrevTime = 1000;
	incrementDifficultyMeanTime = initialIncrementDifficultyMeanTime;
}

Board::~Board() {}

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

	randomEnemy(1.8);
	randomEnemy(2.2);
	randomEnemy(2.2);
	randomEnemy(2.2);
	randomEnemy(2);
	randomEnemy(2.1);
	randomEnemy(2.1);
	randomEnemy(2.1);
	randomEnemy(2.2);
}

void Board::drawItems()
{
	gameItemIterator i = boardItems.begin();
	for (; i != boardItems.end(); i++)
	{
		cout << (*(*i));
	}
	cout<<*myShip;
	wrefresh(win);
}

void Board::randomEnemy(double difficultyLevel)
{
	//get random x form range 0 - difficultyLevel;
	double x = ((rand() % 100) / 100.0) * difficultyLevel;		
	//get random y form range 0 - difficultyLevel;
	double y = ((rand() % 100) / 100.0) * difficultyLevel;
	//get floor of min(x,y)
	int enemyIndex = (int) min(x, y);	

	GameItem * nowy = nullptr;
	switch (enemyIndex)
	{
	case 0:
		nowy = new Stone();
		break;
	case 1:
		nowy = new EnemyShip();
		break;
	case 2:
		nowy = new EnemyShip();
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
	mvwprintw(win, 19, 40, "Poziom trudnosci: %lf", difficultyLevel);
	mvwprintw(win, 20, 40, "Czas enemy insert: %d", insertNewEnemyMeanTime);
	wrefresh(win);
	getch();
}

void Board::update(chrono::milliseconds & time)
{
	updateMovements(time);
	collisionDetect();
	insertEnemy(time);
	if (time.count() - incrementDifficultyPrevTime > incrementDifficultyMeanTime)
	{
		insertNewEnemyMeanTime--;
		difficultyLevel += 0.002;
		incrementDifficultyPrevTime = time.count();
	}
}

void Board::keyHandle(const int & key)
{
	int dS = 1;
	int ctrl = 3*dS;
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
		while (ctrl--)
			if (myShip->move(0, -ctrl))
				break;
		break;
	case CTL_DOWN:
		while (ctrl--)
			if (myShip->move(0, ctrl))
				break;
		break;
	case CTL_RIGHT:
		while (ctrl--)
			if (myShip->move(ctrl, 0))
				break;
		break;
	case CTL_LEFT:
		while (ctrl--)
			if (myShip->move(-ctrl, 0))
				break;
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

void Board::updateMovements(chrono::milliseconds & time)
{	
	EnemyItem::getTargetPosition(myShip);
	gameItemIterator i = boardItems.begin();
	while(i != boardItems.end())
	{
		if (!((*i)->updatePosition(time.count())))
		{
			if(dynamic_cast<Stone *>(*i) != nullptr)
			{
				i = boardItems.erase(i);
				continue;
			}
			if (dynamic_cast<Bullet *>(*i) != nullptr)
			{  
				i = boardItems.erase(i);
				continue;
			}
		}
		i++;
	}
	myShip->updatePosition(time.count());
}

void Board::collisionDetect(void)
{
	gameItemIterator i = boardItems.begin();
	for (; i != boardItems.end(); i++)
	{
		if ((*i)->updateColision(&boardItems, myShip))
		{
			mvwprintw(win, 16, 40, "Trafiono cie !!! ");
		}
	}
		
	if(myShip->updateColision(&boardItems, myShip))
		mvwprintw(win, 16, 40, "Trafiles wrooooga !!! ");
}

void Board::insertEnemy(chrono::milliseconds & time)
{
	if (time.count() - prevInsertTime > newInsertTime)
	{
		randomEnemy(difficultyLevel);
		newInsertTime = (rand() % (2 * insertNewEnemyMeanTime)) + 500;
		prevInsertTime = time.count();
	}
}
//double & Board::probabilityDistributeFunction(double & x, double & difficulty)
//{
//	double out = (-x + difficulty);
//	return out;
//}
