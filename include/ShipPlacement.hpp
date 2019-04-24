#pragma once
#include "Board.h"
#include "TileMovement.hpp"

// Places ship on board
void placeShip(Board &playerBoard, int &curShip, int &shipLength, int curOrientation, bool &isPlayer1, bool &isShipPlacement)
{
	int curX = playerBoard.getCurXPos(), curY = playerBoard.getCurYPos();
	bool valid = true;

	if (curOrientation == HORIZONTAL)
	{
		for (int count = 0; count < shipLength && valid; ++count) // Check if valid
		{
			if (playerBoard.getTileNum(curY, curX).getOccupationType() != WATER)
			{
				valid = false;
			}
			curX++;
		}
		if (valid) // Place Ship
		{
			curX = playerBoard.getCurXPos();
			for (int count = 0; count < shipLength; ++count)
			{
				playerBoard.getTileNum(curY, curX).setTileOccupation(curShip);
				curX++;
			}
		}
	}
	else // VERTICAL
	{
		for (int count = 0; count < shipLength && valid; ++count) // check if valid
		{
			if (playerBoard.getTileNum(curY, curX).getOccupationType() != WATER)
			{
				valid = false;
			}
			curY++;
		}
		if (valid) // Place Ship
		{
			curY = playerBoard.getCurYPos();
			for (int count = 0; count < shipLength; ++count)
			{
				playerBoard.getTileNum(curY, curX).setTileOccupation(curShip);
				curY++;
			}
		}
	}

	if (valid)
	{
		if (curShip != DESTROYER) // more ships to place
		{
			if (curShip != CRUISER) // next ship will be 1 less in length
			{
				shipLength--;
			}
			curShip++; // progress to next ship
		}
		else // no more ships to place
		{
			if (isPlayer1)
			{
				isPlayer1 = false; // switch to player 2
				curShip = CARRIER; // reset to first ship to place (Carrier)
				shipLength = 5;
			}
			else // done placing ships
			{
				isPlayer1 = true; // player 1's turn again
				isShipPlacement = false;
			}
		}
	}
}