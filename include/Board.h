#pragma once
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Tile.h"

class Board : public sf::Drawable {
 public:
  Board(const sf::Color &myColor) {
    int xSize = 40, ySize = 40;
    for (int i = 0; i < 100; ++i) {
      mGrid[i].setOutlineColor(myColor);
      mGrid[i].setPosition(sf::Vector2f(xSize*(i % 10), ySize*(i/10)));
      mGrid[i].setSize(sf::Vector2f(xSize,ySize));
      mGrid[i].setTileOccupation(WATER);
    }

    mColor = myColor;
    mCurXPos = mCurYPos = 0;

    for (int count = 0; count < 5; ++count) {
      mFleet[count] = true;
    }

    mGrid[1].setOutlineColor(sf::Color::Yellow);
  }

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    for (auto i = 0; i < 10; i++) {
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