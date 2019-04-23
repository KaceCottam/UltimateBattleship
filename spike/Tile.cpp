#include "Tile.h"

//bool Tile::getIsOccupied() const
//{
//	return mTileStatus;
//}

int Tile::getOccupationType() const
{
	return mTileStatus;
}

void Tile::setTileOccupation(const int & newOccupation)
{
	mTileStatus = newOccupation;
}

//void Tile::setIsOccupied(const bool & newStatus)
//{
//	mIsOccupied = newStatus;
//}
