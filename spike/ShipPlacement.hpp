#pragma once
#include "Board.h"
#include "TileMovement.hpp"

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
				playerBoard.getTileNum(curY, curX).setFillColor(sf::Color::Magenta);
				playerBoard.getTileNum(curY, curX).setTileOccupation(curShip);
				curX++;
			}
		}
	}
	else // VERTICAL
	{
		for (int count = 0; count < shipLength && valid; ++count)
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
				playerBoard.getTileNum(curY, curX).setFillColor(sf::Color::Magenta);
				playerBoard.getTileNum(curY, curX).setTileOccupation(curShip);
				curY++;
			}
		}
	}

	if (valid)
	{
		if (curShip != DESTROYER)
		{
			if (curShip != CRUISER)
			{
				shipLength--;
			}
			curShip++;
		}
		else
		{
			if (isPlayer1)
			{
				isPlayer1 = false;
				curShip = CARRIER;
				shipLength = 5;
			}
			else
			{
				isPlayer1 = true;
				isShipPlacement = false;
			}
		}
	}
}