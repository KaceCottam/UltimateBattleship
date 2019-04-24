#pragma once

#include "Board.h"
#include "TileMovement.hpp"

enum TypeOfHit
{
	MISS, HIT, INVALID
};


int fire(Board &playerBoard)
{
	int hitType;
	Tile &curTile = playerBoard.getTileNum(playerBoard.getCurYPos(), playerBoard.getCurXPos());
	int tileStatus = curTile.getOccupationType();

	if (tileStatus == WATER)
	{
		hitType = MISS;
		curTile.setFillColor(sf::Color::Cyan);
		curTile.setTileOccupation(PREV_MISS);
		cout << "Miss!" << endl;
	}
	else if (tileStatus == PREV_HIT || tileStatus == PREV_MISS)
	{
		hitType = INVALID;
	}
	else
	{
		hitType = HIT;
		curTile.setFillColor(sf::Color::Magenta);
		curTile.setTileOccupation(PREV_HIT);
		cout << "Hit!" << endl;
	}
	return hitType;
}