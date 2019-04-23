#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Ship.hpp"

class Board : public sf::Drawable
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

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    for (auto i = 0; i < 10; i++)
    {
      for (auto j = 0; j < 10; j++)
      {
        target.draw(getTileNum(i, j));
      }
      
    }
    
  }

  void updateHighlight(int x, int y);
  void updateSecondaryHighlight(int x, int y);
  void resetHighlight();
  void resetFill();
  //void fire(int x, int y);

  int getCurXPos() const;
  int getCurYPos() const;

  bool updateFleetStatus();
  bool isWinner() const;

  Tile getTileNum(int i, int j) const;

private:
  Tile mGrid[10][10];
  bool mFleet[5];
  sf::Color mColor;
  int mCurXPos;
  int mCurYPos;
};