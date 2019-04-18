#pragma once
#include "Tile.h"

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
				xPos += 40;
			}
			yPos += 40;
		}
		
		mColor = myColor;
		mCurXPos = mCurYPos = 0;
	}



	void updateHighlight(int x, int y);
	void fire(int x, int y);

	int getCurXPos();
	int getCurYPos();

	Tile &getTileNum(int i, int j);

private:
	Tile mGrid[10][10];
	sf::Color mColor;
	int mCurXPos;
	int mCurYPos;
};