#pragma once

#include "Board.h"
#include "TileMovement.hpp"

enum TypeOfHit
{
	MISS, HIT, INVALID
};

// Fires at tile that is currently selected - returns if hit, missed, or if it was invalid
int fire(Board &playerBoard)
{
	int hitType;
	
	// get the tile the player fired at
	Tile &curTile = playerBoard.getTileNum(playerBoard.getCurYPos(), playerBoard.getCurXPos());
	
	// find out what the status of the tile was (empty, ship, or already hit)
	int tileStatus = curTile.getOccupationType();

	if (tileStatus == WATER) // Tile was empty (water) - miss
	{
		hitType = MISS;
		curTile.setFillColor(sf::Color::Cyan);
		curTile.setTileOccupation(PREV_MISS); // record that tile has been fired at
		cout << "Miss!" << endl;
	}
	else if (tileStatus == PREV_HIT || tileStatus == PREV_MISS) // tile has already been fired at - invalid
	{
		hitType = INVALID;
	}
	else // tile has a ship - hit
	{
		hitType = HIT;
		curTile.setFillColor(sf::Color::Magenta);
		curTile.setTileOccupation(PREV_HIT); // record that tile has been fired at
		cout << "Hit!" << endl;
	}
	return hitType;
}