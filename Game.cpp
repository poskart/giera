#include "Game.h"

Game::Game()
{
	gameWindow = newwin(gameBoardSizeY, gameBoardSizeX + scoreDisplaySize, 0, 0);
	noecho();
	cbreak();
	// turn on keypad translation for terminal
	keypad(gameWindow, TRUE);

	// Save begin time
	beginTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::playGame(bool newGame)
{
	if(newGame)
		initialize();
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
		plansza->showInfo(timeCounter.count());

		if (c == 's')
			plansza->showItems();
		if (c == 27)
			break;

		Sleep(20);
	}
	getch();
}

void Game::saveGame(const char * fileName)
{
	ofstream fout;
	/*
		failbit - logical error on i/o operation
		badbit - read/writing error on i/o operation
	*/
	fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		fout.open(fileName, ios_base::out | ios_base::binary);
	}
	catch (std::ofstream::failure e)
	{
		throw e;
	}
	gameObjectTypes typeOfObject;

	gameItemIterator tmpIter;
	if (plansza != nullptr)
	{
		tmpIter = plansza->boardItems.begin();
		for (; tmpIter != plansza->boardItems.end(); tmpIter++)
		{
			if (dynamic_cast<MyBullet *>(*tmpIter) != nullptr)
				typeOfObject = mybullet;
			else if (dynamic_cast<EnemyBullet *>(*tmpIter) != nullptr)
				typeOfObject = enemybullet;
			else if (dynamic_cast<SimpleEnemyShip *>(*tmpIter) != nullptr)
				typeOfObject = simpleenemyship;
			else if (dynamic_cast<Stone *>(*tmpIter) != nullptr)
				typeOfObject = stone;

			// Save object type & object itself
			fout.write((char *)&typeOfObject, sizeof(gameObjectTypes));
			GameItem::gameItemInfo tmpStruct = (*tmpIter)->getItemParameters();
			fout.write((char *)(&tmpStruct), sizeof(tmpStruct));
		}

		// Save myShip type & myShip itself
		typeOfObject = myship;
		fout.write((char *)&typeOfObject, sizeof(gameObjectTypes));
		GameItem::gameItemInfo tmpStruct = plansza->myShip->getItemParameters();
		fout.write((char *)(&tmpStruct), sizeof(tmpStruct));

		// Save score
		int sc = plansza->myShip->getScore();
		fout.write((char *)&sc, sizeof(int));
		// Save difficulty level
		double tmpParameter1 = plansza->difficultyLevel;
		fout.write((char *)& tmpParameter1, sizeof(tmpParameter1));
		// Save insertNewEnemyMeanTime
		int tmpParameter2 = plansza->insertNewEnemyMeanTime;
		fout.write((char *)& tmpParameter2, sizeof(tmpParameter2));
	}

	fout.close();
}

void Game::loadGame(const char * fileName)
{
	ifstream fin;
	/*
	failbit - logical error on i/o operation
	badbit - read/writing error on i/o operation
	*/
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		fin.open(fileName, ios_base::in | ios_base::binary);
	}
	catch (std::ifstream::failure e)
	{
		throw e;
	}

	if (plansza != nullptr)
	{
		deleteBoard();
	}
	plansza = new Board();
	plansza->init(gameWindow);

	gameObjectTypes typeOfObject = stone;
	GameItem * itemToInsert = nullptr;
	if (!(fin.eof()))
	{
		while (typeOfObject != myship && !(fin.eof()))
		{
			// Read type of the item
			fin.read((char *)&typeOfObject, sizeof(typeOfObject));

			if (typeOfObject == mybullet)
				itemToInsert = new MyBullet();
			else if (typeOfObject == enemybullet)
				itemToInsert = new EnemyBullet();
			else if (typeOfObject == simpleenemyship)
				itemToInsert = new SimpleEnemyShip();
			else if (typeOfObject == stone)
				itemToInsert = new Stone();
			else if (typeOfObject == myship)
				itemToInsert = new MyShip();

			GameItem::gameItemInfo tmpStruct;
			// Read the item
			fin.read((char *)(& tmpStruct), sizeof(tmpStruct));
			// Set new item's parameters
			itemToInsert->setItemParameters(tmpStruct);

			// Insert new game item into GameItem container
			if (typeOfObject == myship)
				plansza->myShip = dynamic_cast<MyShip *>(itemToInsert);
			else
				plansza->boardItems.push_back(itemToInsert);
		}
		// Read score
		fin.read((char *)&(plansza->myShip->getScoreRef()), sizeof(int));
		// Read difficulty level
		fin.read((char *)(&plansza->difficultyLevel), sizeof(double));
		// Read insertNewEnemyMeanTime
		fin.read((char *)(&plansza->insertNewEnemyMeanTime), sizeof(int));
	}
	fin.close();
}

void Game::deleteBoard()
{
	if (plansza != nullptr)
	{
		plansza->clear();
		delete plansza;
	}
}

void Game::initialize()
{
	plansza = new Board();//155, 
	plansza->init(gameWindow);
	plansza->initializeItems();
	plansza->drawFrame();
	plansza->drawItems();
}

bool Game::isBoardInitialized(void)
{
	return plansza != nullptr;
}

void Game::updateGameTime(void)
{
	// Save begin time
	beginTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
}