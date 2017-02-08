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

/*
	Method init(WINDOW * fromGame) initlializes all functionalities 
	which are needed during board items processing. It sets current
	window pointer, initializes random numbers, and initializes frame's
	character arrays.
*/
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

/*
	Method drawFrame() draws frame in current window
*/
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
}

/*
	Method initializeItems(void) creates myShip and pushes
	some enemy items to the board.
*/
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

/*
	Method drawItems() draws all game items on the board
	(in current window).
*/
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
	int enemyIndex = (int)min(	(int)min(x, y), 2	);	

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
		nowy = new EnemyDestroyer();
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

/*
	Method showStatistic(void) prints item's count on the board 
	and game state variables.
*/
void Board::showStatistic(void)
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

/*
	Method update(chrono::milliseconds & time) executes an 
	appropriate action for each of game item depending on the
	current time, inserts new enemy items and updates game
	state variables.
*/
bool Board::update(chrono::milliseconds & time)
{
	bool ifEndOfTheGame = false;
	// Update item's movements & attack
	updateMovementsAndAttack(time);
	// Update item's collisions & check if myShip not destroyed
	ifEndOfTheGame = collisionDetect();
	// Insert enemy if it's time
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

/*
	Method keyHandle(const int & key) perform an appropriate
	action in response to given, pressed key.
*/
void Board::keyHandle(const int & key)
{
	int dS = 1;
	int ctrlPressedDistance = 3*dS;
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
		while (ctrlPressedDistance--)
			if (myShip->move(0, -ctrlPressedDistance))
				break;
		break;
	case CTL_DOWN:
		while (ctrlPressedDistance--)
			if (myShip->move(0, ctrlPressedDistance))
				break;
		break;
	case CTL_RIGHT:
		while (ctrlPressedDistance--)
			if (myShip->move(ctrlPressedDistance, 0))
				break;
		break;
	case CTL_LEFT:
		while (ctrlPressedDistance--)
			if (myShip->move(-ctrlPressedDistance, 0))
				break;
		break;
	// Fire conventional missile
	case ' ':
	{
		position pos = myShip->getPosition();
		Bullet * bul = new MyBullet(pos.x, pos.y);
		myShip->shoot(bul, &boardItems);
		break;
	}
	// Fire guided missile if doesn't exist
	case 'g':
	{
		if (myShip->getGuidedMissilePtr() == nullptr)
		{
			position pos = myShip->getPosition();
			Bullet * bul = new GuidedMissile(pos.x, pos.y);
			myShip->shoot(bul, &boardItems);
			myShip->setGuidedMissilePtr(dynamic_cast<GuidedMissile *>(bul));
		}
		break;
	}
	// Fire triple missile
	case 't':
	{
		position pos = myShip->getPosition();
		TripleMissile * bul = nullptr;
		for (int i = -1; i < 2; i++)
		{
			bul = new TripleMissile(pos.x, pos.y);
			bul->setHorizontalSpeed(i*4);
			myShip->shoot(dynamic_cast<Bullet *>(bul), &boardItems);
		}
		break;
	}
	// Move guided missile to the left (if exists)
	case 'a':
		if (myShip->getGuidedMissilePtr() != nullptr)
		{
			myShip->getGuidedMissilePtr()->move(-1, 0);
		}
		break;
	// Move guided missile to the right (if exists)
	case 'd':
		if (myShip->getGuidedMissilePtr() != nullptr)
		{
			myShip->getGuidedMissilePtr()->move(1, 0);
		}
		break;
	default:
		//refresh();
		break;
	}
}

/*
	Method updateMovementsAndAttack(time) updates position of each of the
	item on the board depending on current time and also trigger enemies 
	attack. Item can be moved by (x, y) or deleted if it's position cannot
	be updated (e.g. went to the end of the board).
*/
void Board::updateMovementsAndAttack(chrono::milliseconds & time)
{	
	// Update target for every enemy item (target = myShip)
	EnemyItem::updateTargetPosition(myShip);
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
				// If it was gMissile - delete myShip pointer to gMissile
				if (dynamic_cast<GuidedMissile *>(*i) != nullptr)
				{
					myShip->setGuidedMissilePtr(nullptr);
				}
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
	gameItemIterator i = boardItems.begin();
	if (i == boardItems.end())
		return false;
	GameItem * itemToDelete;
	GameItem * itemHitByI;
	while( i != boardItems.end())
	{
		//If there i-th item hit sth
		if ((itemHitByI = (*i)->updateColision(&boardItems, myShip)) != nullptr)
		{
			//if myShip was hit by Bullet
			if (itemHitByI == myShip)
			{
				//bullet hit myShip
				if (! (myShip->loseHealth((*i)->getFirepower())))
					return true;
				itemToDelete = *i;
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
			
			if (dynamic_cast<Bullet *>(*i) != nullptr)
			{
				// If myBullet hit sth
				if (dynamic_cast<MyBullet *>(*i) != nullptr)
				{
					myShip->AddPoints(itemHitByI->getPointsForDestroy());
					// If it was gMissile - delete myShip pointer to gMissile
					if (dynamic_cast<GuidedMissile *>(*i) != nullptr)
					{
						myShip->setGuidedMissilePtr(nullptr);
					}
					if (dynamic_cast<EnemyDestroyer *>(itemHitByI) != nullptr)
					{
						itemHitByI->loseHealth((*i)->getFirepower());
						if (!itemHitByI->isAlive())
						{
							boardItems.remove(itemHitByI);
							delete itemHitByI;
						}
						itemToDelete = *i;
						i = boardItems.erase(i);
						delete itemToDelete;
						continue;
					}
				}
				// if (EnemyBullet) hit MyBullet
				else if (dynamic_cast<MyBullet *>(itemHitByI) != nullptr)
				{
					myShip->AddPoints((*i)->getPointsForDestroy());
					// If it was gMissile - delete myShip pointer to gMissile
					if (dynamic_cast<GuidedMissile *>(itemHitByI) != nullptr)
					{
						myShip->setGuidedMissilePtr(nullptr);
					}
				}
				boardItems.remove(itemHitByI);
				delete itemHitByI;
				itemToDelete = *i;
				i = boardItems.erase(i);
				delete itemToDelete;
				continue;
			}
			// Stone hit sth (myShip)
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
		i++;
	}
	return false;
}

/*
	insertEnemy(time) method inserts an enemy item to the board
	items container, when it's time. Also updates newInsert time,
	which is random value from the given range of time.
*/
void Board::insertEnemy(chrono::milliseconds & time)
{
	if (time.count() - prevInsertTime > newInsertTime)
	{
		randomEnemy(difficultyLevel);
		newInsertTime = (rand() % (2 * insertNewEnemyMeanTime)) + 500;
		prevInsertTime = time.count();
	}
}

/*
	Method clear() clears every item from gameItemContainer & 
	makes it empty.
*/
void Board::clear(void)
{
	gameItemIterator i = boardItems.begin();
	while(i != boardItems.end())
	{
		delete *(i++);
	}
	boardItems.clear();
}

/*
	Method showInfo(time) shows info about game time, health & score.
*/
void Board::showInfo(int gameTimeMs)
{
	mvwprintw(win, 2, boardSizeX + 5, "Czas gry: %d", gameTimeMs/1000);
	mvwprintw(win, 5, boardSizeX + 5, "Pozostalo zycia: %d%%", myShip->getLife());
	mvwprintw(win, 7, boardSizeX + 5, "Punkty: %d", myShip->getScore());
}

//double & Board::probabilityDistributeFunction(double & x, double & difficulty)
//{
//	double out = (-x + difficulty);
//	return out;
//}
