#pragma once
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Tile.h"

class Board : public sf::Drawable {
 public:
  Board(const sf::Color &myColor) {
    int xPos = 10, yPos = 10;
    for (int i = 0; i < 100; ++i) {
      mGrid[i].setOutlineColor(myColor);
      mGrid[i].setPosition(sf::Vector2f(xPos, yPos));
      mGrid[i].setSize(sf::Vector2f(40, 40));
      mGrid[i].setTileOccupation(WATER);
    }

    mColor = myColor;
    mCurXPos = mCurYPos = 0;

    for (int count = 0; count < 5; ++count) {
      mFleet[count] = true;
    }
  }

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    for (auto i = 0; i < 100; i++) {
      for (auto j = 0; j < 10; j++) {
        target.draw(getTileNum(i, j));
      }
    }
  }

  void updateHighlight(int x, int y);
  void updateSecondaryHighlight(int x, int y);
  void resetHighlight();
  void resetFill();

  int getCurXPos() const;
  int getCurYPos() const;

  bool updateFleetStatus();
  bool isWinner() const;

  Tile getTileNum(int i, int j) const;

 private:
  std::array<Tile, 100> mGrid;
  std::array<bool, 5> mFleet;
  sf::Color mColor;
  int mCurXPos;
  int mCurYPos;
};