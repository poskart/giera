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

Game::~Game()	{}

/*
	Method playGame(bool newGame) initializes new game if newGame 
	argument is true or provide an existing game otherwise. Method 
	ends it's execution when game is finished or 'Esc' key was pressed.
*/
void Game::playGame(bool newGame)
{
	if(newGame)
		initialize();
	// Do not block keyboard for gameWindow - read each of characters separately
	wtimeout(gameWindow, 0);

	int inputCharacter = 0;
	fflush(stdin);

	// No delay mode enabled
	nodelay(gameWindow, true);
	while (1)
	{
		// Update time counter
		timeCounter = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			) - beginTime;

		// Wait for key pressed
		inputCharacter = wgetch(gameWindow);
		
		// Update ship behavior
		plansza->keyHandle(inputCharacter);

		// Check if MyShip not destroyed
		if (!(plansza->update(timeCounter)))
			break;

		// Update board view
		wclear(gameWindow);
		plansza->drawFrame();
		plansza->drawItems();
		plansza->showInfo(timeCounter.count());
		wrefresh(gameWindow);

		// Show game statistics
		if (inputCharacter == 's')
			plansza->showStatistic();
		// Escape
		if (inputCharacter == 27)
			break;

		Sleep(20);
	}
	getch();
}

/*
	Method saveGame(const char * fileName) saves a game state into 
	binary file fileName. saveGame() also covers error handling 
	releted to file operations.

	File structure (binary):
		1_gameObjectType (enum), 1_gameItemInfo (struct), 2_gameObjectType (enum), 
		2_gameItemInfo (struct), ..., ith_gameObjectType (enum), ith_gameItemInfo (struct), ...
		myShip gameObjectType (enum), myShip gameItemInfo (struct)
		score (int), difficultyLevel (double), insertNewEnemyMeanTime (int)
*/
void Game::saveGame(const char * fileName)
{
	ofstream fout;
	/*
		failbit - logical error on i/o operation
		badbit - read/writing error on i/o operation
	*/
	fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	// Try to open file fileName
	try
	{
		fout.open(fileName, ios_base::out | ios_base::binary);
	}
	catch (std::ofstream::failure e)
	{
		throw e;
	}
	// If plansza not empty, save game state to the file
	if (plansza != nullptr)
	{	
		gameObjectTypes typeOfObject;
		gameItemIterator tmpIter = plansza->boardItems.begin();
		for (; tmpIter != plansza->boardItems.end(); tmpIter++)
		{
			if (dynamic_cast<GuidedMissile *>(*tmpIter) != nullptr)
				typeOfObject = guidedmissile;
			else if (dynamic_cast<TripleMissile *>(*tmpIter) != nullptr)
				typeOfObject = triplemissile;
			else if (dynamic_cast<EnemyDestroyer *>(*tmpIter) != nullptr)
				typeOfObject = enemydestroyer;
			else if (dynamic_cast<EnemyGuidedMissile *>(*tmpIter) != nullptr)
				typeOfObject = enemyguidedmissile;
			else if (dynamic_cast<MyBullet *>(*tmpIter) != nullptr)
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

/*
	Method loadGame(const char * fileName) loads a game state from
	binary file fileName. loadGame() also covers error handling
	releted to file operations.

	File structure (binary):
		1_gameObjectType (enum), 1_gameItemInfo (struct), 2_gameObjectType (enum),
		2_gameItemInfo (struct), ..., ith_gameObjectType (enum), ith_gameItemInfo (struct), ...
		myShip gameObjectType (enum), myShip gameItemInfo (struct)
		score (int), difficultyLevel (double), insertNewEnemyMeanTime (int)
*/
void Game::loadGame(const char * fileName)
{
	ifstream fin;
	/*
		failbit - logical error on i/o operation
		badbit - read/writing error on i/o operation
	*/
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// Try to open file fileName
	try
	{
		fin.open(fileName, ios_base::in | ios_base::binary);
	}
	catch (std::ifstream::failure e)
	{
		throw e;
	}
	// Delete board if yet initialized
	deleteBoard();
	// Initialize new, empty board
	plansza = new Board();
	plansza->init(gameWindow);

	gameObjectTypes typeOfObject = stone;
	GameItem * itemToInsert = nullptr;
	// Check if file is not empty
	if (!(fin.eof()))
	{
		// Continue reading until myShip item found
		while (typeOfObject != myship && !(fin.eof()))
		{
			// Read type of the item
			fin.read((char *)&typeOfObject, sizeof(typeOfObject));
			if (typeOfObject == guidedmissile)
				itemToInsert = new GuidedMissile();
			else if (typeOfObject == triplemissile)
				itemToInsert = new TripleMissile();
			else if (typeOfObject == enemydestroyer)
				itemToInsert = new EnemyDestroyer();
			else if (typeOfObject == enemyguidedmissile)
				itemToInsert = new EnemyGuidedMissile();
			else if (typeOfObject == mybullet)
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

/*
	Delete board items and board object itself it board exists
*/
void Game::deleteBoard()
{
	if (plansza != nullptr)
	{
		plansza->clear();
		delete plansza;
	}
}

/*
	Method initialize() game to be ready to play. Creates new board object, 
	initalizes game window, initialize board items (sample enemies etc.) and
	drows board & items.
*/
void Game::initialize()
{
	plansza = new Board();
	plansza->init(gameWindow);
	plansza->initializeItems();
	plansza->drawFrame();
	plansza->drawItems();
}

/*
	Method isBoardInitialized(void) returns true when board
	has been already initialized, false otherwise.
*/
bool Game::isBoardInitialized(void)
{
	return plansza != nullptr;
}

/*
	Method updateGameTime(void) overwrites game begin time 
	with the current time in miliseconds.
*/
void Game::updateGameTime(void)
{
	// Save begin time
	beginTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
}