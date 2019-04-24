#pragma once
#include "Tile.h"
//#include "Ship.h"

class Board
{
public:
	Board(const sf::Color &myColor)
	{
		int xPos = 10, yPos = 10;
		for (int i = 0; i < 10; ++i)
		{
			xPos = 10;
			for (int j = 0; j < 10; ++j)
			{
				mGrid[i][j].setOutlineColor(myColor);
				mGrid[i][j].setPosition(sf::Vector2f(xPos, yPos));
				mGrid[i][j].setSize(sf::Vector2f(40, 40));
				mGrid[i][j].setTileOccupation(WATER);
				xPos += 40;
			}
			yPos += 40;
		}
		
		mColor = myColor;
		mCurXPos = mCurYPos = 0;

		for (int count = 0; count < 5; ++count)
		{
			mFleet[count] = true;
		}

	}



	void updateHighlight(int x, int y);
	void updateSecondaryHighlight(int x, int y);
	void resetHighlight();
	void resetFill();
	//void fire(int x, int y);

	int getCurXPos();
	int getCurYPos();

	bool updateFleetStatus();
	bool isWinner();

	Tile &getTileNum(int i, int j);

private:
	Tile mGrid[10][10];
	bool mFleet[5];
	sf::Color mColor;
	int mCurXPos;
	int mCurYPos;
};