#include "Tile.h"

bool Tile::getIsOccupied() const
{
	return mIsOccupied;
}

void Tile::setIsOccupied(const bool & newStatus)
{
	mIsOccupied = newStatus;
}
