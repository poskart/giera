/*
 * GameItem.cpp
 *
 *  Created on: 3 gru 2015
 *      Author: piotr
 */

#include "GameItem.h"

WINDOW * GameItem::win = NULL;

GameItem::GameItem()
{
	lifePercentage = 100;
	movementSpeed = 1;
	lastUpdateTime = 0;
	firepower = 0;
}

GameItem::~GameItem()
{
	// TODO Auto-generated destructor stub
}

void GameItem::setCommonWindow(WINDOW * fromGame)
{
	GameItem::win = fromGame;
}

void GameItem::setLife(int & percent)
{
	lifePercentage = percent;
}

int GameItem::getLife(void)
{
	return lifePercentage;
}

bool GameItem::isAlive(void)
{
	return lifePercentage > 0;
}

int GameItem::getFirepower(void)
{
	return firepower;
}

position GameItem::getPosition(void)
{
	return coordinates;
}

void GameItem::forcePosition(position & nowa)
{
	coordinates = nowa;
}

ostream & operator<< (ostream & os, const GameItem & gi)
{
	gi.draw(os);
	return os;
}

/*
	Method move() moves GameItem dx distance about dx and dy about dy
	and returns true if item was moved in x or in y direction.
*/
bool GameItem::move(const int & dx, const int & dy)
{
	bool wasMoved = false;
	position aux{ this->coordinates.x + dx, this->coordinates.y + dy };
	this->forcePosition(aux);
	if (!this->whetherCollideWithWallsX(*this) && dx != 0)
	{
		wasMoved = true;
	}
	else
		this->coordinates.x -= dx;
	if (!this->whetherCollideWithWallsY(*this) && dy != 0)
	{
		wasMoved = true;
	}
	else
		this->coordinates.y -= dy;

	return wasMoved;
}

/*
	Set coords as the new position of the object (after creation)
*/
bool GameItem::setPosition(position & coords)
{
	coordinates = coords;
	return true;
}

/*
	Method whetherCollideWithPosition() returns true if GameItem collides with
	position potentialCollide, otherwise it returns false.
*/
bool GameItem::whetherCollideWithPosition(const position * potentialCollide)
{
	if ((*potentialCollide) == coordinates)
		return true;
	position * tmpPos = getPointsOfBody();
	for (int i = 0; i < getNumberOfBodyPoints(); i++, tmpPos++)
	{
		if ((*potentialCollide) == ((*tmpPos) + coordinates))//((potentialCollide->x == (tmpPos->x + coordinates.x)) && (potentialCollide->y == (tmpPos->y + coordinates.y)))
			return true;
	}
	return false;
}

/*
	Method whetherCollideWithWalls() returns true if GameItem collides with
	any wall (left, right, bottom, upper).
*/
bool GameItem::whetherCollideWithWalls(const GameItem & jakis) const
{
	if (whetherCollideWithWallsX(jakis) && whetherCollideWithWallsY(jakis))
		return true;
	return false;
}

/*
	Method whetherCollideWithWallsX() returns true if GameItem collides with
	wheter left or right wall
*/
bool GameItem::whetherCollideWithWallsX(const GameItem & jakis) const
{
	if (isXinsideBoard(jakis.coordinates.x + maxXofPoints(getPointsOfBody(), getNumberOfBodyPoints()))
		&& isXinsideBoard(jakis.coordinates.x + minXofPoints(getPointsOfBody(), getNumberOfBodyPoints())))
		return false;
	return true;
}

/*
	Method whetherCollideWithWallsY() returns true if GameItem collides with
	wheter upper or bottom wall
*/
bool GameItem::whetherCollideWithWallsY(const GameItem & jakis) const
{
	if (isYinsideBoard(jakis.coordinates.y + maxYofPoints(getPointsOfBody(), getNumberOfBodyPoints()))
		&& isYinsideBoard(jakis.coordinates.y + minYofPoints(getPointsOfBody(), getNumberOfBodyPoints())))
		return false;
	return true;
}

/*
	 Draw game item on the board depending on it's type.
	 This method is generic.
*/
void GameItem::draw(ostream & where) const  
{
	// Take character from specified object and print middle part of it's body
	mvwprintw(win, coordinates.y, coordinates.x, "%c", this->getMainCharacter());
	// Get others points of object's body
	position * pos = this->getPointsOfBody();
	if (pos != nullptr)
	{
		for (int i = 0; i < this->getNumberOfBodyPoints(); i++)
		{
			mvwprintw(win, coordinates.y + pos[i].y, coordinates.x + pos[i].x,
				"%c", this->getMainCharacter());
		}
	}
}

/*
	Method updatePosition() updates position (coordinates) of GameItem
	according to its type. This method should be specified for each of the 
	inherited object.
*/
bool GameItem::updatePosition(long int ms)
{
	return false;
}

/*
	Method updateColision(), checks if any collision with the other GameItens
	occured. If so, it returns this, otherwise (it collision did not occured)
	it returns false.
*/
GameItem * GameItem::updateColision(gameItemContainer * boardItems, GameItem * myShip)
{
	return nullptr;
}

// Return true if given x position is included in the board
bool isXinsideBoard(int x)
{
	if( x < (gameBoardSizeX -1) && x > 0)
		return true;
	return false;
}

// Return true if given y position is included in the board
bool isYinsideBoard(int y)
{
	if( y < (gameBoardSizeY - 1) && y > 0)
		return true;
	return false;
}

// Return max x coordinate from given array of points (x, y)
int maxXofPoints(position * array, const int & N)
{
	int maxX = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].x > maxX)
			maxX = array[i].x;
	return maxX;
}

// Return max y coordinate from given array of points (x, y)
int maxYofPoints(position * array, const int & N)
{
	int maxY = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].y > maxY)
			maxY = array[i].y;
	return maxY;
}

// Return min x coordinate from given array of points (x, y)
int minXofPoints(position * array, const int & N)
{
	int minX = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].x < minX)
			minX = array[i].x;
	return minX;
}

// Return min x coordinate from given array of points (x, y)
int minYofPoints(position * array, const int & N)
{
	int minY = 0;
	for(int i = 0 ; i < N  ; i++)
		if(array[i].y < minY)
			minY = array[i].y;
	return minY;
}