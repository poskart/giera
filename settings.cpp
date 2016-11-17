#include "settings.h"

position operator+(const position & pos1, const position & pos2)
{
	position outcome;
	outcome.x = pos1.x + pos2.x;
	outcome.y = pos1.y + pos2.y;
	return outcome;
}

bool operator==(const position & pos1, const position & pos2)
{
	if ((pos1.x == pos2.x) && (pos1.y == pos2.y))
		return true;
	else
		return false;
}