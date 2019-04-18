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

void Board::fire(int x, int y)
{
	if (mGrid[y][x].getIsOccupied() == true)
	{
		mGrid[y][x].setFillColor(sf::Color::Magenta);
	}
	else
	{
		mGrid[y][x].setFillColor(sf::Color::Cyan);
	}
}

int Board::getCurXPos()
{
	return mCurXPos;
}

int Board::getCurYPos()
{
	return mCurYPos;
}

Tile& Board::getTileNum(int i, int j)
{
	return mGrid[i][j];
}
