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
	win = nullptr;
	myShip = nullptr;
	difficultyLevel = initialDifficultyLevel;
	insertNewEnemyMeanTime = initialInsertNewEnemyMeanTime;
	prevInsertTime = 1000;
	newInsertTime = 1000;
	incrementDifficultyPrevTime = 1000;
	incrementDifficultyMeanTime = initialIncrementDifficultyMeanTime;
}

Board::Board(WINDOW * fromGame) : Board::Board()
{
	win = fromGame;
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

void Board::initializeItems(void)
{
	myShip = new MyShip();

	Stone * kamien = new Stone(45, 22);
	boardItems.push_back(kamien);

	SimpleEnemyShip * nowy = new SimpleEnemyShip(30, 15);
	boardItems.push_back(nowy);

	nowy = new SimpleEnemyShip(60, 15);
	boardItems.push_back(nowy);

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
	if (i != boardItems.end())
	{
		for (; i != boardItems.end(); i++)
		{
			cout << (*(*i));
		}
	}
	cout<<*myShip;
	wrefresh(win);
}

/*
	Function inserts random enemy based on given difficulty level.
	The greater value of difficultyLevel, the greater likelihood is
	that harder enemy is choosen.
*/
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
		nowy = new SimpleEnemyShip();
		break;
	case 2:
		nowy = new SimpleEnemyShip();
		break;
	default:
		break;
	}

	if (nowy != NULL)
	{
		// We must know size of new enemy to prevent from placing it
		// incorrectly, e.g in the board wall
		int N = nowy->getNumberOfBodyPoints();
		position * bodyPointsTable = nowy->getPointsOfBody();

		int maxXSizeOfItem = max(maxXofPoints(bodyPointsTable, N),
			(-1)*minXofPoints(bodyPointsTable, N));

		position randPosition{ (rand() % (boardSizeX - 2 * maxXSizeOfItem) + 1 + maxXSizeOfItem),
			(-1)*minYofPoints(bodyPointsTable, N) + 1 };

		nowy->setPosition(randPosition);
		boardItems.push_back(nowy);
	}
}

void Board::showItems(void)
{
	int SimpleEnemyShips = 0, stones = 0;
	gameItemIterator it = boardItems.begin();
	if (it == boardItems.end())
		return;
	for (; it != boardItems.end(); it++)
	{
		if (dynamic_cast<SimpleEnemyShip *>(*it) != nullptr)
			SimpleEnemyShips++;
		else if (dynamic_cast<Stone *>(*it) != nullptr)
			stones++;
		else;
	}
	mvwprintw(win, 16, 40, "Counted objects:");
	mvwprintw(win, 17, 40, "Enemy ships: %d", SimpleEnemyShips);
	mvwprintw(win, 18, 40, "Stones: %d", stones);
	mvwprintw(win, 19, 40, "Difficulty level: %lf", difficultyLevel);
	mvwprintw(win, 20, 40, "Enemy insert mean time: %d", insertNewEnemyMeanTime);
	wrefresh(win);
	getch();
}

bool Board::update(chrono::milliseconds & time)
{
	bool ifEndOfTheGame = false;
	updateMovements(time);
	ifEndOfTheGame = collisionDetect();
	insertEnemy(time);
	// Check if it is time to update difficulty level & insertNewEnemyMeanTime
	if (time.count() - incrementDifficultyPrevTime > incrementDifficultyMeanTime)
	{
		// Insert enemies more often
		if(insertNewEnemyMeanTime > 500)
			insertNewEnemyMeanTime--;
		// Increment difficulty level
		if(difficultyLevel < 3)
			difficultyLevel += 0.002;
		incrementDifficultyPrevTime = time.count();
	}
	return !ifEndOfTheGame;
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
		myShip->shoot(bul, &boardItems);
		break;
	}
	default:
		//refresh();
		break;
	}
}

void Board::updateMovements(chrono::milliseconds & time)
{	
	EnemyItem::getTargetPosition(myShip);
	gameItemIterator i = boardItems.begin();
	if (i == boardItems.end())
		return;
	GameItem * itemToDelete;
	while(i != boardItems.end())
	{
		if (!((*i)->updatePosition(time.count())))
		{
			//if stone went to the end of the board
			if(dynamic_cast<Stone *>(*i) != nullptr)
			{
				itemToDelete = (*i);
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
			//if bullet went to the end of the board
			if (dynamic_cast<Bullet *>(*i) != nullptr)
			{  
				itemToDelete = (*i);
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
		}
		//Every enemy ship shoot when it's commited to shoot
		if (dynamic_cast<SimpleEnemyShip *>(*i) != nullptr)
		{
			SimpleEnemyShip * tmpShip = dynamic_cast<SimpleEnemyShip *>((*i));
			tmpShip->shootIfShould(&boardItems, time.count());
		}
		i++;
	}
}

/*
	Method collisionDetect() handles collisions of items with MyShip.
	It updates state of MyShip. Returns true if MyShip was destroyed,
	false otherwise.
*/
bool Board::collisionDetect(void)
{
	int tmp = 1;
	gameItemIterator i = boardItems.begin();
	if (i == boardItems.end())
		return false;
	GameItem * tmpPtr = (*i);
	GameItem * itemToDelete;
	while( i != boardItems.end())
	{
		//If there sth hit sth
		if ((tmpPtr = (*i)->updateColision(&boardItems, myShip)) != nullptr)
		{
			//if myShip was hit by Bullet
			if (tmpPtr == myShip)
			{
				//bullet hit myShip
				if (! (myShip->loseHealth((*i)->getFirepower())))
					return true;
				itemToDelete = *i;
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
			
			(*i) = tmpPtr;
			if (dynamic_cast<Bullet *>(*i) != nullptr)
			{
				if (dynamic_cast<MyBullet *>(*i) != nullptr)
				{
					myShip->AddPoints(100);
				}
				else
					;
				itemToDelete = *i;
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
			else if (dynamic_cast<Stone *>(*i) != nullptr)
			{
				//Stone hit myShip
				if (!(myShip->loseHealth((*i)->getFirepower())))
					return true;
				itemToDelete = *i;
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
		}
		tmp++;
		i++;
	}
	return false;
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

void Board::clear(void)
{
	boardItems.clear();
}

void Board::showInfo(void)
{
	mvwprintw(win, 2, boardSizeX + 5, "Pozostalo zycia: %d%%", myShip->getLife());
	mvwprintw(win, 4, boardSizeX + 5, "Punkty: %d", myShip->getScore());
	wrefresh(win);
}

//double & Board::probabilityDistributeFunction(double & x, double & difficulty)
//{
//	double out = (-x + difficulty);
//	return out;
//}
