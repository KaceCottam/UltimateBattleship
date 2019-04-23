#include "Board.h"

void Board::updateHighlight(int x, int y)
{
	if (x < 0 || y < 0)
	{
		if (x < 0)
		{
			x = 9;
		}
		if (y < 0)
		{
			y = 9;
		}
	}
	else
	{
		x = x % 10;
		y = y % 10;
	}

	mGrid[mCurYPos][mCurXPos].setOutlineColor(mColor);
	mCurXPos = x;
	mCurYPos = y;
	mGrid[mCurYPos][mCurXPos].setOutlineColor(sf::Color::Yellow);
}

void Board::updateSecondaryHighlight(int x, int y)
{
	mGrid[y][x].setOutlineColor(sf::Color::Yellow);
}

void Board::resetHighlight()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			mGrid[i][j].setOutlineColor(mColor);
		}
	}
}

void Board::resetFill()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			mGrid[i][j].setFillColor(sf::Color::Transparent);
		}
	}
}

//void Board::fire(int x, int y)
//{
//	if (mGrid[y][x].getIsOccupied() == true)
//	{
//		mGrid[y][x].setFillColor(sf::Color::Magenta);
//	}
//	else
//	{
//		mGrid[y][x].setFillColor(sf::Color::Cyan);
//	}
//}

int Board::getCurXPos()
{
	return mCurXPos;
}

int Board::getCurYPos()
{
	return mCurYPos;
}

bool Board::updateFleetStatus()
{
	bool newShipSunk = false;
	int numGone = 0;
	int occupationType = 0;
	bool found = false;

	for (int currentSearch = CARRIER; currentSearch <= DESTROYER; ++currentSearch)
	{
		for (int i = 0; i < 10 && !found; ++i)
		{
			for (int j = 0; j < 10 && !found; ++j)
			{
				occupationType = mGrid[i][j].getOccupationType();
				if (occupationType == currentSearch)
				{
					found = true;
				}
			}
		}
		
		if (!found)
		{
			//cout << "It gets here" << endl;
			if (mFleet[currentSearch - 1])
			{
				cout << "Ship Type: " << currentSearch << " has been sunk!" << endl;
				mFleet[currentSearch - 1] = false;
				newShipSunk = true;
			}
		}
		found = false;
	}
	
	return newShipSunk;
}

bool Board::isWinner()
{
	bool winner = true;

	for (int count = 0; count < 5 && winner; ++count)
	{
		if (mFleet[count])
		{
			winner = false;
		}
	}
	return winner;
}

Tile& Board::getTileNum(int i, int j) const
{
	return mGrid[i][j];
}
