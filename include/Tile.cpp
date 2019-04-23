#include "Tile.h"

int Tile::getOccupationType() const
{
	return mTileStatus;
}

void Tile::setTileOccupation(const int & newOccupation)
{
	mTileStatus = newOccupation;
}